#include "common/Logging.h"

#include "CBaseEntity.h"

#include "CEntityDict.h"

namespace
{
static CEntityDict g_EntityDict;
}

CEntityDict& GetEntityDict()
{
	return g_EntityDict;
}

bool CEntityDict::HasEntity( const char* const pszClassName ) const
{
	return FindEntity( pszClassName ) != nullptr;
}

const CBaseEntityRegistry* CEntityDict::FindEntity( const char* const pszClassName ) const
{
	assert( pszClassName );

	auto it = m_Dict.find( pszClassName );

	return it != m_Dict.end() ? it->second : nullptr;
}

bool CEntityDict::AddEntity( const CBaseEntityRegistry* pRegistry )
{
	assert( pRegistry );

	if( FindEntity( pRegistry->GetClassName() ) )
	{
		//This shouldn't happen, since there'd be duplicate symbols in the library.
		//TODO: replace with FatalError
		Error( "CEntityDict::AddEntity: Duplicate entity \"%s\" added!\n", pRegistry->GetClassName() );
		return false;
	}

	m_Dict.insert( std::make_pair( pRegistry->GetClassName(), pRegistry ) );

	return true;
}

CBaseEntity* CEntityDict::CreateEntity( const char* const pszClassName ) const
{
	const auto pReg = FindEntity( pszClassName );

	if( !pReg )
		return nullptr;

	if( CBaseEntity* pEntity = pReg->Create() )
	{
		pEntity->Construct( pszClassName );
		pEntity->OnCreate();

		return pEntity;
	}

	return nullptr;
}

void CEntityDict::DestroyEntity( CBaseEntity* pEntity ) const
{
	assert( pEntity );

	const auto pReg = FindEntity( pEntity->GetClassName() );

	if( !pReg )
	{
		//TODO: replace with FatalError
		Error( "CEntityDict::DestroyEntity: Tried to destroy unknown entity \"%s\"!\n", pEntity->GetClassName() );
		return;
	}

	pEntity->OnDestroy();

	pReg->Destroy( pEntity );
}
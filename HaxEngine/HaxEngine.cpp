#include "HaxEngine.h"
#include "../Hax_App/Hax_ROS_Esp.h"

std::shared_ptr <CHaxApp> g_haxApp = nullptr;

CHaxEngine::CHaxEngine(EGameCodes eGameCode) :
	m_eGameCode(eGameCode)
{
	m_pRosHaxMgr = std::make_shared<CROS_ESP_Hax>();
}

void CHaxEngine::RegisterHaxApp(const std::shared_ptr <CHaxApp> & haxApp)
{
	g_haxApp = haxApp;
}

void CHaxEngine::OnAppNotification(bool bCreated)
{
	switch (m_eGameCode)
	{
		case GAME_CODE_ROS:
		{
			if (bCreated)
				m_pRosHaxMgr->Initialize();
			else
				m_pRosHaxMgr->Finalize();
		} break;
	}
}


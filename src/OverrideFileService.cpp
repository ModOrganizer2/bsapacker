#include "OverrideFileService.h"

#include "SettingsService.h"
#include <QFile>

namespace BsaPacker
{
	const uint16_t FALLOUT_3_NEXUS_ID = 120;
	const uint16_t NEW_VEGAS_NEXUS_ID = 130;

	OverrideFileService::OverrideFileService(const ISettingsService* settingsService) : m_SettingsService(settingsService)
	{
	}

	// TODO: Add detection for Command Extender and JIP LN NVSE and warn if missing
	bool OverrideFileService::CreateOverrideFile(const int nexusId, const QString& archiveName) const
	{
		if (!this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_CREATE_OVERRIDES).toBool()) {
			return false;
		}

		if (nexusId != FALLOUT_3_NEXUS_ID && nexusId != NEW_VEGAS_NEXUS_ID) {
			return false;
		}

		QFile file(archiveName.left(archiveName.lastIndexOf(".") + 1) + "override");
		if (file.exists()) {
			return true;
		}

		if (!file.open(QIODeviceBase::NewOnly)) {
			qWarning() << "Failed to create file " << file.fileName();
			return false;
		}
		file.close();
		return true;
	}
}
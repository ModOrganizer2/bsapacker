#ifndef OVERRIDEFILESERVICE_H
#define OVERRIDEFILESERVICE_H

#include "bsapacker_global.h"
#include <bsapacker/IOverrideFileService.h>
#include <bsapacker/ISettingsService.h>

namespace BsaPacker
{
	class BSAPACKER_EXPORT OverrideFileService : public IOverrideFileService
	{
	public:
		OverrideFileService(const ISettingsService* settingsService);
		bool CreateOverrideFile(const int nexusId, const QString& archiveName) const override;

	private:
		const ISettingsService* m_SettingsService = nullptr;
	};
}

#endif // OVERRIDEFILESERVICE_H

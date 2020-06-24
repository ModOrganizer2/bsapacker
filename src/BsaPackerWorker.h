#ifndef BSAPACKERWORKER_H
#define BSAPACKERWORKER_H

#include <bsapacker/ISettingsService.h>
#include <bsapacker/IModDtoFactory.h>
#include <bsapacker/IArchiveBuilderFactory.h>
#include <bsapacker/IArchiveAutoService.h>
#include <bsapacker/IDummyPluginServiceFactory.h>
#include <bsapacker/IHideLooseAssetService.h>
#include <bsapacker/IArchiveNameService.h>

namespace BsaPacker
{
	class BsaPackerWorker
	{
	public:
		BsaPackerWorker(
			const ISettingsService* settingsService,
			const IModDtoFactory* modDtoFactory,
			const IArchiveBuilderFactory* archiveBuilderFactory,
			const IArchiveAutoService* archiveAutoService,
			const IDummyPluginServiceFactory* dummyPluginService,
			const IHideLooseAssetService* hideLooseAssetService,
			const IArchiveNameService* archiveNameService);
		void DoWork() const;

	private:
		const ISettingsService* m_SettingsService = nullptr;
		const IModDtoFactory* m_ModDtoFactory = nullptr;
		const IArchiveBuilderFactory* m_ArchiveBuilderFactory = nullptr;
		const IArchiveAutoService* m_ArchiveAutoService = nullptr;
		const IDummyPluginServiceFactory* m_DummyPluginServiceFactory = nullptr;
		const IHideLooseAssetService* m_HideLooseAssetService = nullptr;
		const IArchiveNameService* m_ArchiveNameService = nullptr;
	};
}

#endif // BSAPACKERWORKER_H

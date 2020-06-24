#include "BsaPackerWorker.h"

#include <QMessageBox>

#include <bsapacker/ArchiveBuildDirector.h>
#include <bsapacker/ModDtoFactory.h>

namespace BsaPacker
{
	BsaPackerWorker::BsaPackerWorker(
		const ISettingsService* settingsService,
		const IModDtoFactory* modDtoFactory,
		const IArchiveBuilderFactory* archiveBuilderFactory,
		const IArchiveAutoService* archiveAutoService,
		const IDummyPluginServiceFactory* dummyPluginServiceFactory,
		const IHideLooseAssetService* hideLooseAssetService,
		const IArchiveNameService* archiveNameService) :
		m_SettingsService(settingsService),
		m_ModDtoFactory(modDtoFactory),
		m_ArchiveBuilderFactory(archiveBuilderFactory),
		m_ArchiveAutoService(archiveAutoService),
		m_DummyPluginServiceFactory(dummyPluginServiceFactory),
		m_HideLooseAssetService(hideLooseAssetService),
		m_ArchiveNameService(archiveNameService)
	{
	}

	void BsaPackerWorker::DoWork() const
	{
		const std::unique_ptr<IModDto> modDto = this->m_ModDtoFactory->Create(); // handles PackerDialog and validation, implements Null Object pattern
		const std::vector<bsa_archive_type_e> types = this->m_ArchiveBuilderFactory->GetArchiveTypes(modDto.get());
		for (auto&& type : types) {
			const std::unique_ptr<IArchiveBuilder> builder = this->m_ArchiveBuilderFactory->Create(type, modDto.get());
			ArchiveBuildDirector director(this->m_SettingsService, builder.get());
			director.Construct(); // must check if cancelled
			const std::unique_ptr<BSArchiveAuto> archive = builder->getArchive();
			if (archive) {
				const QString& archiveFullPath = this->m_ArchiveNameService->GetArchiveFullPath(type, modDto.get());
				this->m_ArchiveAutoService->CreateBSA(archive.get(), archiveFullPath, type);
				QMessageBox::information(nullptr, "", QObject::tr("Created") + " \"" + archiveFullPath + "\"");
			}
		}
		const std::unique_ptr<IDummyPluginService> pluginService = this->m_DummyPluginServiceFactory->Create();
		pluginService->CreatePlugin(modDto->Directory(), modDto->ArchiveName());

		if (!modDto->Directory().isEmpty()) {
			this->m_HideLooseAssetService->HideLooseAssets(modDto->Directory());
		}
	}
}

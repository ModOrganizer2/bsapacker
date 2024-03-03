#include <BsaPacker.h>

#include <bsapacker/ArchiveAutoService.h>
#include <bsapacker/ArchiveBuildDirector.h>
#include <bsapacker/ArchiveBuilderHelper.h>
#include <bsapacker/ArchiveBuilderFactory.h>
#include <ArchiveNameService.h>
#include "BsaPackerWorker.h"
#include "DummyPluginLogic.h"
#include "DummyPluginServiceFactory.h"
#include "FileWriterService.h"
#include "HideLooseAssetService.h"
#include "ModContext.h"
#include "ModDto.h"
#include "PackerDialog.h"
#include "SettingsService.h"
#include <bsapacker/ModDtoFactory.h>
#include <QMessageBox>
#include <iplugingame.h>

#include <boost/di.hpp>
namespace di = boost::di;

namespace BsaPacker
{
	bool Bsa_Packer::init(MOBase::IOrganizer* moInfo)
	{
		this->m_Organizer = moInfo;
		this->m_ModContext = std::make_unique<ModContext>(this->m_Organizer);
		this->m_SettingsService = std::make_unique<SettingsService>(this->m_Organizer);
		return true;
	}

	QString Bsa_Packer::name() const
	{
		return QStringLiteral("BSA Packer");
	}

	QString Bsa_Packer::author() const
	{
		return QStringLiteral("MattyFez");
	}

	QString Bsa_Packer::description() const
	{
		return tr("Transform loose files into a Bethesda Softworks Archive file (.bsa/.ba2).");
	}

	MOBase::VersionInfo Bsa_Packer::version() const
	{
		return MOBase::VersionInfo(1, 0, 4, MOBase::VersionInfo::RELEASE_FINAL);
	}

	QList<MOBase::PluginSetting> Bsa_Packer::settings() const
	{
		return SettingsService::PluginSettings;
	}

	QString Bsa_Packer::tooltip() const
	{
		return tr("Transform loose files into a Bethesda Softworks Archive file (.bsa/.ba2).");
	}

	QIcon Bsa_Packer::icon() const
	{
		return QIcon();
	}

	QString Bsa_Packer::displayName() const
	{
		return tr("BSA Packer");
	}

	void Bsa_Packer::display() const
	{
		const auto injector = di::make_injector(
			di::bind<IModContext>.to(this->m_ModContext.get()),
			di::bind<ISettingsService>.to(this->m_SettingsService.get()),
			di::bind<IModDtoFactory>.to<ModDtoFactory>(),
			di::bind<IArchiveBuilderHelper>.to<ArchiveBuilderHelper>(),
			di::bind<IArchiveBuilderFactory>.to<ArchiveBuilderFactory>(),
			di::bind<IArchiveAutoService>.to<ArchiveAutoService>(),
			di::bind<IDummyPluginServiceFactory>.to<DummyPluginServiceFactory>(),
			di::bind<IFileWriterService>.to<FileWriterService>(),
			di::bind<IArchiveNameService>.to<ArchiveNameService>(),
			di::bind<IDummyPluginLogic>.to<DummyPluginLogic>(),
			di::bind<IHideLooseAssetService>.to<HideLooseAssetService>(),
			di::bind<IPackerDialog>.to<PackerDialog>()
		);

		BsaPackerWorker worker = di::create<BsaPackerWorker>(injector);
		worker.DoWork();
	}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
	Q_EXPORT_PLUGIN2(myTool, BSA_Packer)
#endif

} // namespace BsaPacker

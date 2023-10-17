#include "StarfieldDummyPluginService.h"

namespace BsaPacker
{
	StarfieldDummyPluginService::StarfieldDummyPluginService(
		const IFileWriterService* fileWriterService,
		const IDummyPluginLogic* dummyPluginLogic)
		: m_FileWriterService(fileWriterService),
		m_DummyPluginLogic(dummyPluginLogic)
	{
	}

	bool StarfieldDummyPluginService::CreatePlugin(const QString& modPath,
		const QString& archiveNameBase) const
	{
		const QString& fileNameNoExtension = modPath + '/' + archiveNameBase;
		if (!this->m_DummyPluginLogic->canCreateDummyESL(fileNameNoExtension, bsa_archive_type_e::baFO4) && !this->m_DummyPluginLogic->canCreateDummyESL(fileNameNoExtension, bsa_archive_type_e::baFO4dds))
		{
			return false;
		}
		const std::string& absoluteFileName = fileNameNoExtension.toStdString() + ".esl";
		return this->m_FileWriterService->Write(absoluteFileName,
			reinterpret_cast<const char*>(StarfieldDummyPluginService::RAW_STARFIELD),
			sizeof(StarfieldDummyPluginService::RAW_STARFIELD));
	}
}

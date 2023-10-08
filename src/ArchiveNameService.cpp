#include "ArchiveNameService.h"

#include "NexusId.h"

namespace BsaPacker
{
	ArchiveNameService::ArchiveNameService(const IModContext* modContext)
		: m_ModContext(modContext)
	{
	}

	QString ArchiveNameService::GetFileExtension() const
	{
		switch (this->m_ModContext->GetNexusId()) {
		case NexusId::Morrowind:
		case NexusId::Oblivion:
		case NexusId::Fallout3:
		case NexusId::NewVegas:
		case NexusId::Skyrim:
		case NexusId::SkyrimSE:
			return QStringLiteral(".bsa");
		case NexusId::Fallout4:
		case  NexusId::Starfield:
			return QStringLiteral(".ba2");
		default:
			return QString();
		}
	}

	QString ArchiveNameService::GetArchiveFullPath(const bsa_archive_type_e type, const IModDto* modDto) const
	{
		return QDir::toNativeSeparators(modDto->Directory() + '/' + modDto->ArchiveName() + this->Infix(type) + this->GetFileExtension());
	}

	QString ArchiveNameService::Infix(const bsa_archive_type_e type) const
	{
		switch (type) {
		case baFO4:
			return QStringLiteral(" - Main");
		case baFO4dds:
			return QStringLiteral(" - Textures");
		case baTES3:
		case baTES4:
		case baFO3:
		case baSSE:
		case baNone:
		default:
			return QString();
		};
	}
}
#include <bsapacker/ArchiveAutoService.h>

namespace BsaPacker
{
	void ArchiveAutoService::CreateBSA(BSArchiveAuto* archive, const QString& archiveName, const bsa_archive_type_e type) const
	{
		archive->create(archiveName, type);
		archive->save();
	}
} // namespace BsaPacker

#include <bsapacker/ArchiveAutoService.h>

namespace BsaPacker
{
	bool ArchiveAutoService::CreateBSA(libbsarch::bs_archive_auto* archive, const QString& archiveName, const bsa_archive_type_e type) const
	{
		try {
			archive->save_to_disk(archiveName.toStdString());
		}
		catch (std::exception e) {
			return false;
		}
		return true;
	}
} // namespace BsaPacker

#ifndef IARCHIVEBUILDERHELPER_H
#define IARCHIVEBUILDERHELPER_H

#include <QDir>
#include <QString>
#include <QStringList>
#include <cstdint>

namespace BsaPacker
{
	class IArchiveBuilderHelper
	{
	public:
		virtual ~IArchiveBuilderHelper() = default;
		[[nodiscard]] virtual bool isFileIgnorable(const QString&, const QStringList&) const = 0;
		[[nodiscard]] virtual bool isIncompressible(const QString&) const = 0;
		[[nodiscard]] virtual bool isExtensionBlacklisted(const QString&) const = 0;
		[[nodiscard]] virtual uint32_t getFileCount(const QDir&) const = 0;
		[[nodiscard]] virtual QStringList getRootDirectoryFilenames(const QDir&) const = 0;
	};
} // namespace BsaPacker

#endif // IARCHIVEBUILDERHELPER_H

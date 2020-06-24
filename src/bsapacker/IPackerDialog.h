#ifndef IPACKERDIALOG_H
#define IPACKERDIALOG_H

#include <QString>
#include <QDialog>
#include <QListWidgetItem>

namespace BsaPacker
{
	class IPackerDialog : public QDialog
	{
		Q_OBJECT

	public:
		virtual ~IPackerDialog() override = default;
		[[nodiscard]] virtual bool IsNewFilename() const = 0;
		[[nodiscard]] virtual QString SelectedMod() const = 0;
		virtual void RefreshModList() = 0;
		[[nodiscard]] virtual QString SelectedPluginItem() const = 0;
		virtual void UpdateNameList(const QString& modName) = 0;
		virtual void RefreshSelectedName() = 0;

	public Q_SLOTS:
		virtual void RefreshOkButton() = 0;
	};
} // namespace BsaPacker

Q_DECLARE_INTERFACE(BsaPacker::IPackerDialog, "com.MattyFez.BSA_Packer/1.0")

#endif // IPACKERDIALOG_H

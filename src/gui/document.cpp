#include "document.h"
#include "documentline.h"
#include "ui_document.h"
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>

Document::Document(QWidget *parent) : QWidget(parent), ui(new Ui::Document) {
  ui->setupUi(this);

  auto widget = ui->scrollAreaWidgetContents;

  ((QVBoxLayout *)widget->layout())->insertWidget(0, new DocumentLine(widget));
}

Document::~Document() { printf("Closed documentus :c\n"); };

// FIXME: Closes regardless of option picked
void Document::closeEvent(QCloseEvent *event) {
  bool shouldClose = this->closeDocument();

  if (!shouldClose)
    event->ignore();
  else
    event->accept();
}

/**
 * @brief Returns the name of the document
 * @return: QString: The name of the document. Is suffixed with "*" if the
 * document is unsaved
 */
QString Document::getName() {
  QString name = m_DocumentName;

  if (unsavedChanges())
    name += "*";

  return name;
}

/**
 * @brief Returns the state of the document
 * @return bool: Returns true if the document has been changed since its last
 * save to disk
 */
bool Document::unsavedChanges() { return m_UnsavedChanged; }

/**
 * @brief Saves the document to disk and updates its saved state
 * @return bool: whether or not the save to disk was successful
 */
bool Document::save() {
  // QString path = QFileDialog::getExistingDirectory (this, tr("Directory"),
  // "");
  QFileDialog::Options options;
  options.setFlag(QFileDialog::Option::DontUseNativeDialog, false);
  QString file = QFileDialog::getSaveFileName(
      nullptr, tr("Save file"), "",
      tr("OpenBirch Document File (*.obdf);;All Files (*.*)"), nullptr,
      options);

  if (file.isEmpty())
    return false;

  if (!file.endsWith(".obdf"))
    file = file + ".obdf";

  printf("Saved file with name \"%s\"", file.toStdString().c_str());

  QStringList parts = file.split("/");
  QString name = parts.last().split(".").first();

  m_DocumentName = name;

  QTabWidget *parent = ((QTabWidget *)this->parentWidget()->parentWidget());
  parent->setTabText(parent->indexOf(this), name);

  // Convert lines array into json data, then save
  QStringList test = {"2x+4=4", "Math", "x=2", "Output",
                      "3",      "Text", "4",   "Text"};

  QFile fileHandle(file);
  fileHandle.open(QFile::WriteOnly);

  fileHandle.write(test.join("\n").toStdString().c_str());

  m_UnsavedChanged = false;
  return true;
}

/**
 * @brief Closes the document and creates a save dialog if there are unsaved
 * changes
 * @return int: returns the button that was clicked in the dialog
 */
bool Document::closeDocument() {

  printf("OOh, i have to close :3\n");

  if (!unsavedChanges()) // if we dont have any unsaved changes just close
  {
    delete this;
    return true;
  }

  QMessageBox msgBox;
  msgBox.setWindowTitle("Unsaved Changes");
  msgBox.setText("This document contains unsaved changes.\nAre you sure you "
                 "want to close it?");
  msgBox.setStandardButtons(QMessageBox::Discard);
  msgBox.addButton(QMessageBox::Save);
  msgBox.addButton(QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Cancel);

  int reply = msgBox.exec();

  if (reply == QMessageBox::Discard)
    return true;
  else if (reply == QMessageBox::Save)
    return this->save();

  // Option must be cancel, return false
  return false;
}
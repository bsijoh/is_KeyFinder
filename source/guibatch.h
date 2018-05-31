/*************************************************************************

  Copyright 2011-2015 Ibrahim Sha'ath

  This file is part of KeyFinder.

  KeyFinder is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  KeyFinder is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with KeyFinder.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

#ifndef BATCHWINDOW_H
#define BATCHWINDOW_H

// forward declaration for circular dependency
class MainMenuHandler;

#include <QtCore>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QFuture>
#include <QFutureWatcher>
#include <QClipboard>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>
#include <QtNetwork/QNetworkReply>

#include "guimenuhandler.h"
#include "preferences.h"
#include "asynckeyprocess.h"
#include "asyncmetadatareadprocess.h"
#include "metadatafilename.h"
#include "externalplaylistprovider.h"
#include "_VERSION.h"

enum playlist_columns_t{
  COL_PLAYLIST_NAME
};

enum track_columns_t{
  COL_STATUS,
  COL_FILEPATH,
  COL_FILENAME,
  COL_TAG_TITLE,
  COL_TAG_ARTIST,
  COL_TAG_ALBUM,
  COL_TAG_COMMENT,
  COL_TAG_GROUPING,
  COL_TAG_KEY,
  COL_DETECTED_KEY
};

namespace Ui {
  class BatchWindow;
}

class BatchWindow : public QMainWindow {
  Q_OBJECT

public:

  explicit BatchWindow(QWidget* parent, MainMenuHandler* handler);
  bool receiveUrls(const QList<QUrl>&);
  ~BatchWindow();

public slots:

  void checkForNewVersion();

private:

  void closeEvent(QCloseEvent*);
  Preferences prefs;
  void setGuiDefaults();
  void setGuiRunning(const QString&, bool);

  void sortTableWidget();

  int libraryOldIndex;
  QFutureWatcher<QList<ExternalPlaylist> >* readLibraryWatcher;
  QFutureWatcher<QList<QUrl> >* loadPlaylistWatcher;
  QList<ExternalPlaylist> libraryPlaylists;

  void dragEnterEvent(QDragEnterEvent*);
  void dropEvent(QDropEvent*);
  QList<QUrl> droppedFiles;
  void addDroppedFiles();
  QFutureWatcher<void>* addFilesWatcher;
  QList<QUrl> getDirectoryContents(QDir) const;

  void addNewRow(QString);
  QFutureWatcher<MetadataReadResult>* metadataReadWatcher;
  void readMetadata();

  QFutureWatcher<KeyFinderResultWrapper>* analysisWatcher;
  void checkRowsForSkipping();
  bool fieldAlreadyHasKeyData(int, int, metadata_write_t);
  void markRowSkipped(int,bool);
  void runAnalysis();

  bool writeToTagsAtRow(int, KeyFinder::key_t);
  bool writeToFilenameAtRow(int, KeyFinder::key_t);

  // UI
  Ui::BatchWindow* ui;
  QPointer<QLabel> initialHelpLabel;
  MainMenuHandler* menuHandler;
  QBrush keyFinderRow;
  QBrush keyFinderAltRow;
  QBrush textDefault;
  QBrush textSuccess;
  QBrush textError;
  bool allowSort;
  int sortColumn;
  std::vector<unsigned int> metadataColumnMapping;

private slots:

  void on_libraryWidget_cellClicked(int,int);
  void headerClicked(int);

  void readLibraryFinished();

  void addFilesFinished();
  void on_runBatchButton_clicked();
  void on_cancelBatchButton_clicked();
  void copySelectedFromTableWidget();
  void writeDetectedToFiles();
  void clearDetected();
  void deleteSelectedRows();

  void analysisFinished();
  void analysisResultReadyAt(int);

  void metadataReadFinished();
  void metadataReadResultReadyAt(int);

  void progressRangeChanged(int, int);
  void progressValueChanged(int);

  void receiveNetworkReply(QNetworkReply*);
};

#endif

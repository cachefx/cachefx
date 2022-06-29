#ifndef CONFIGWINDOWVIEW_H
#define CONFIGWINDOWVIEW_H

#include <QObject>
#include <QWidget>
#include <memory>

class QGroupBox;
class QPushButton;
class QListView;
class QStringListModel;
class QSpinBox;
class QComboBox;
class QLabel;
class QTreeView;
class QCloseEvent;
class ConfigWindowPresenter;
class QStandardItemModel;

class ConfigWindowView : public QWidget
{
  Q_OBJECT
public:
  explicit ConfigWindowView(QWidget* parent = 0);
  virtual ~ConfigWindowView();

  void setListCaches(QStringListModel* cacheList);
  void setListCacheTypes(QStringListModel* cacheTypeList);
  void setCachePropertyTable(QStandardItemModel* propertyTable);
  void setListCacheSelected(int row);
  void setCacheTypeSelected(int idx);
  void setNLines(int value);
  int getNLines();
  void registerPresenter(ConfigWindowPresenter* presenter);
  int getSelectedCacheIdx();
  QString getSelectedReplAlgorithm();
  void setSelectedReplAlgorithm(QString algo);
  void installReplAlgComboBox(int row, QStringListModel* replAlgList,
                              ConfigWindowPresenter* presenter);
  virtual void closeEvent(QCloseEvent* event);

signals:
  void saveConfigFile();

private:
  QGroupBox* qBoxCaches;
  QPushButton* qButtonUp;
  QPushButton* qButtonDown;
  QPushButton* qButtonRemove;
  QPushButton* qButtonNew;
  QListView* qListCaches;

  QGroupBox* qBoxCacheConfig;
  QLabel* qLabelNLines;
  QLabel* qLabelNLinesData;
  QLabel* qLabelCacheType;
  QComboBox* qComboCacheType;
  QLabel* qLabelProperties;
  QTreeView* qTreeProperties;
  QComboBox* qComboReplAlg;
};

#endif // CONFIGWINDOWVIEW_H

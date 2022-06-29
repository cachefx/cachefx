#ifndef CONFIGWINDOWPRESENTER_H_
#define CONFIGWINDOWPRESENTER_H_

#include <Cache/Cache.h>
#include <Cache/CacheHierarchy.h>
#include <CacheFactory/CacheFactory.h>
#include <QModelIndexList>
#include <QObject>
#include <memory>

class ConfigWindowView;
class QStringListModel;
class QStandardItemModel;
class QStandardItem;
class ConfigWindowPresenter : public QObject
{
  Q_OBJECT
public:
  ConfigWindowPresenter(ConfigWindowView* v, std::string configFile);
  virtual ~ConfigWindowPresenter();

public slots:
  void upButtonClicked();
  void downButtonClicked();
  void removeButtonClicked();
  void newButtonClicked();
  void cacheListSelectionChanged(QModelIndex indexNew, QModelIndex indexOld);
  void cacheTypeSelectionChanged(int index);
  void cachePropertyChanged(QStandardItem* item);
  void algorithmSelectionChanged(QString algo);
  void saveConfigurationFile();

private:
  void initView();
  QStringList getCacheList();
  QStringList getCacheTypeList();
  QStringList getReplAlgList();
  CacheHierarchy* getCacheHierarchy();
  void updateCacheDescription();
  void updateCacheModel();
  void createPropertyTableModel(Cache* cache);

private:
  ConfigWindowView* view;
  std::unique_ptr<Cache> cacheHierarchy;
  QStringListModel* cacheListModel;
  QStringListModel* cacheTypeListModel;
  QStringListModel* replAlgListModel;
  QStandardItemModel* cachePropertiesModel;
  int selectedCacheIndex;

  std::map<replAlg, std::string> repAlgStrMap;
  std::map<std::string, replAlg> strRepAlgMap;

  std::string cfgFilePath;

  static const char* PROPERTY_CACHE_NSETS;
  static const char* PROPERTY_CACHE_NWAYS;
  static const char* PROPERTY_CACHE_NSECWAYS;
  static const char* PROPERTY_CACHE_REPLALG;
  static const char* PROPERTY_CACHE_NBITS;
  static const char* PROPERTY_CACHE_KBITS;
  static const char* PROPERTY_CACHE_NPARTITIONS;
  static const char* PROPERTY_CACHE_NRANDOMSETS;
};

#endif /* CONFIGWINDOWPRESENTER_H_ */

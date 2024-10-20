#pragma once

#include <list>
#include <map>
#include <memory>

#include "../uiwindow.h"
#include "../menuselectoption.h"

class TransferManager;
class TransferStatus;
class MenuSelectOptionElement;

struct TransferDetails {
  std::string route;
  std::string timespent;
  std::string progress;
  std::string timeremaining;
  std::string speed;
  std::string transferred;
  std::string timestamp;
  std::string path;
};

struct TransferFilteringParameters {
  TransferFilteringParameters() :
    usejobfilter(false), usesitefilter(false), usefilenamefilter(false),
    usestatusfilter(false), showstatusinprogress(false),
    showstatusdone(false), showstatusfail(false), showstatusdupe(false),
    usespeedbelowfilter(false), speedbelowfilter(0),
    usespeedabovefilter(false), speedabovefilter(0) { }
  bool usejobfilter;
  std::list<std::string> spreadjobsfilter;
  std::list<std::string> transferjobsfilter;
  bool usesitefilter;
  std::list<std::string> sourcesitefilters;
  std::list<std::string> targetsitefilters;
  std::list<std::string> anydirectionsitefilters;
  bool usefilenamefilter;
  std::string filenamefilter;
  bool usestatusfilter;
  bool showstatusinprogress;
  bool showstatusdone;
  bool showstatusfail;
  bool showstatusdupe;
  bool usespeedbelowfilter;
  unsigned int speedbelowfilter;
  bool usespeedabovefilter;
  unsigned int speedabovefilter;
};

class TransfersScreen : public UIWindow {
public:
  TransfersScreen(Ui *);
  ~TransfersScreen();
  void initialize(unsigned int row, unsigned int col);
  void initializeFilterSite(unsigned int row, unsigned int col, const std::string& site);
  void initializeFilterSpreadJob(unsigned int row, unsigned int col, const std::string& job);
  void initializeFilterTransferJob(unsigned int row, unsigned int col, const std::string& job);
  void initializeFilterSpreadJobSite(unsigned int row, unsigned int col, const std::string& job, const std::string& site);
  void initialize(unsigned int row, unsigned int col, const TransferFilteringParameters& tfp);
  void redraw() override;
  bool keyPressed(unsigned int) override;
  std::string getLegendText() const override;
  std::string getInfoLabel() const override;
  std::string getInfoText() const override;
  static void addTransferTableHeader(unsigned int y, MenuSelectOption& mso);
  static TransferDetails formatTransferDetails(std::shared_ptr<TransferStatus>& ts);
private:
  static void addTransferTableRow(unsigned int, MenuSelectOption &, bool,
      const std::string &, const std::string &, const std::string &,
      const std::string &, const std::string &, const std::string &,
      const std::string &, const std::string &, const std::string &,
      int);
  static void addTransferDetails(unsigned int, MenuSelectOption &, std::shared_ptr<TransferStatus>, int);
  void addFilterFinishedTransfers();
  bool showsWhileFiltered(const std::shared_ptr<TransferStatus>& ts) const;
  unsigned int totalListSize() const;
  std::map<int, std::shared_ptr<TransferStatus> > statusmap;
  TransferManager * tm;
  MenuSelectOption table;
  unsigned int currentviewspan;
  unsigned int ypos;
  bool hascontents;
  int nextid;
  bool filtering;
  TransferFilteringParameters tfp;
  int numfinishedfiltered;
  std::list<std::shared_ptr<TransferStatus> > finishedfilteredtransfers;
  bool temphighlightline;
};

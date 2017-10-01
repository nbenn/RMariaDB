#ifndef __RMARIADB_MARIA_RESULT_PREP__
#define __RMARIADB_MARIA_RESULT_PREP__

#include <boost/noncopyable.hpp>
#include "MariaConnection.h"
#include "MariaBinding.h"
#include "MariaResult.h"
#include "MariaRow.h"
#include "MariaTypes.h"
#include "MariaUtils.h"

class MariaResultPrep : boost::noncopyable, public MariaResult {
  MariaConnectionPtr pConn_;
  MYSQL_STMT* pStatement_;
  MYSQL_RES* pSpec_;
  uint64_t rowsAffected_, rowsFetched_;

  int nCols_, nParams_;
  bool bound_, complete_;

  std::vector<MariaFieldType> types_;
  std::vector<std::string> names_;
  MariaBinding bindingInput_;
  MariaRow bindingOutput_;

public:
  MariaResultPrep(MariaConnectionPtr pConn, const std::string& sql);
  ~MariaResultPrep();
  void discard();

public:
  virtual void send_query();
  virtual void close();

  virtual void bind(List params);

  virtual List column_info();

  virtual List fetch(int n_max = -1);

  virtual int rows_affected();
  virtual int rows_fetched();
  virtual bool complete();
  virtual bool active();

private:
  void execute();

  bool has_result() const;
  bool step();
  bool fetch_row();
  void throw_error();
  void throw_error_and_discard();

private:
  void cache_metadata();
};

#endif

#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
using namespace std;

class InMemoryDB{
private:
  //storage of the main database
  unordered_map<string,int> database;

  //storage of transaction
  unordered_map<string, int> transaction;

  //flag to track if transaction is in progress;
  bool in_progress;

public:
  InMemoryDB() : in_progress(false) {}

  //get value for a key
  int get(const std::string &key) {
    //check transaction storage if in transaction in progress
    if (in_progress && transaction.find(key) != transaction.end()) {
        return transaction[key];
    }

    //if key not in transaction storage check main database
    if (database.find(key) != database.end()) {
        return database[key];
    }

    throw std::runtime_error("Error! This key does not exist");
  }
  
  //put a key-value pair
  void put(const string& key, int value){
    if(!in_progress){
      throw runtime_error("There is no transaction in progress");
    }

    transaction[key] = value;
  }

  //begin a new transaction
  void begin_transaction(){
    if(in_progress){
      throw runtime_error("There is a transaction already in progress! Please end this transaction to begin a new one");
    }

    transaction.clear();
    in_progress = true;
  }

  //commit the current transaction
  void commit(){
    if(!in_progress){
      throw runtime_error("There is no transaction in progress");
    }

    //apply all changes from transaction storage to main
    for(const auto& [key,value]: transaction){
      database[key] = value;
    }

    //clear transaction storage and reset flag
    transaction.clear();
    in_progress = false;
  }

  //rollback current transaction 
  void rollback(){
    if (!in_progress) {
              throw std::runtime_error("No transaction in progress");
          }
          
          //clear transaction storage and reset flag
          transaction.clear();
          in_progress = false;
      }
};
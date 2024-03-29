#ifndef AnalysisExample_MiniTree_H
#define AnalysisExample_MiniTree_H

#include "xAODAnaHelpers/HelpTreeBase.h"
#include "TTree.h"

class MiniTree : public HelpTreeBase
{

  private:
    bool m_firstEvent;

  public:

    MiniTree(xAOD::TEvent * event, TTree* tree, TFile* file, xAOD::TStore* store = nullptr);
    ~MiniTree();

    void AddEventUser( const std::string detailStr = "" );
    void AddJetsUser( const std::string detailStr = "", const std::string jetName = "jet" );
    void FillEventUser( const xAOD::EventInfo* eventInfo);
    void FillJetsUser( const xAOD::Jet* jet, const std::string jetName = "jet" );
    void ClearEventUser();
    void ClearJetsUser(const std::string jetName = "jet");
};
#endif

#pragma once

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"

#include <memory>
#include <utility>

namespace seahorn {

class GateAnalysis;

class GateAnalysisPass : public llvm::FunctionPass {
public:
  static char ID;

  GateAnalysisPass() : llvm::FunctionPass(ID) {}

  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
  virtual bool runOnFunction(llvm::Function &F) override;

  llvm::StringRef getPassName() const override { return "GateAnalysisPass"; }
  void print (llvm::raw_ostream &os, const llvm::Module *M) const override;

  GateAnalysis& getGateAnalysis() {
    assert(m_analysis);
    return *m_analysis;
  }

private:
  std::unique_ptr<GateAnalysis> m_analysis;
};

llvm::FunctionPass *createGateAnalysisPass();

class GateAnalysis {
public:
  virtual ~GateAnalysis() = default;

  virtual llvm::Value* getGamma(llvm::PHINode *PN) const = 0;
  virtual bool isThinned() const = 0;
};

}

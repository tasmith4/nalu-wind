// Copyright 2017 National Technology & Engineering Solutions of Sandia, LLC
// (NTESS), National Renewable Energy Laboratory, University of Texas Austin,
// Northwest Research Associates. Under the terms of Contract DE-NA0003525
// with NTESS, the U.S. Government retains certain rights in this software.
//
// This software is released under the BSD 3-clause license. See LICENSE file
// for more details.
//


#ifndef TKESSTDESNODEKERNEL_H
#define TKESSTDESNODEKERNEL_H

#include "node_kernels/NodeKernel.h"
#include "FieldTypeDef.h"

#include "stk_mesh/base/BulkData.hpp"
#include "stk_mesh/base/Ngp.hpp"
#include "stk_mesh/base/NgpField.hpp"
#include "stk_mesh/base/Types.hpp"

namespace sierra {
namespace nalu {

class Realm;

class TKESSTDESNodeKernel : public NGPNodeKernel<TKESSTDESNodeKernel>
{
public:
  TKESSTDESNodeKernel(const stk::mesh::MetaData&);

  TKESSTDESNodeKernel() = delete;

  KOKKOS_FUNCTION
  virtual ~TKESSTDESNodeKernel() = default;

  virtual void setup(Realm&) override;

  KOKKOS_FUNCTION
  virtual void execute(
    NodeKernelTraits::LhsType&,
    NodeKernelTraits::RhsType&,
    const stk::mesh::FastMeshIndex&) override;

private:
  stk::mesh::NgpField<double> tke_;
  stk::mesh::NgpField<double> sdr_;
  stk::mesh::NgpField<double> density_;
  stk::mesh::NgpField<double> tvisc_;
  stk::mesh::NgpField<double> dudx_;
  stk::mesh::NgpField<double> dualNodalVolume_;
  stk::mesh::NgpField<double> maxLenScale_;
  stk::mesh::NgpField<double> fOneBlend_;

  unsigned tkeID_             {stk::mesh::InvalidOrdinal};
  unsigned sdrID_             {stk::mesh::InvalidOrdinal};
  unsigned densityID_         {stk::mesh::InvalidOrdinal};
  unsigned tviscID_           {stk::mesh::InvalidOrdinal};
  unsigned dudxID_            {stk::mesh::InvalidOrdinal};
  unsigned dualNodalVolumeID_ {stk::mesh::InvalidOrdinal};
  unsigned maxLenScaleID_     {stk::mesh::InvalidOrdinal};
  unsigned fOneBlendID_       {stk::mesh::InvalidOrdinal};

  NodeKernelTraits::DblType betaStar_;
  NodeKernelTraits::DblType tkeProdLimitRatio_;
  NodeKernelTraits::DblType cDESke_;
  NodeKernelTraits::DblType cDESkw_;
  NodeKernelTraits::DblType relaxFac_;

  const int nDim_;
};

}  // nalu
}  // sierra


#endif /* TKESSTDESNODEKERNEL_H */

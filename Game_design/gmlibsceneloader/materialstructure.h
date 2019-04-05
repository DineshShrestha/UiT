#ifndef MATERIALSTRUCTURE_H
#define MATERIALSTRUCTURE_H
#include "sceneobjectstructure.h"


#include "setmaterialstructure.h"

class MaterialStructure : public SetMaterialStructure
{
public:
    MaterialStructure();
    ~MaterialStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription,
                                  const Structure *structure ) const override;

};
#endif // MATERIALSTRUCTURE_H

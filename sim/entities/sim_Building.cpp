#include <sim/entities/sim_Building.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

const std::string Building::m_tagName = "building";

////////////////////////////////////////////////////////////////////////////////

Building::Building( Affiliation affiliation ) : UnitGround( affiliation ) {}

////////////////////////////////////////////////////////////////////////////////

Building::~Building() {}

////////////////////////////////////////////////////////////////////////////////

void Building::updateCollisions() {}

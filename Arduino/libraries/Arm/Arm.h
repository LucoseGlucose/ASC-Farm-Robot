

float ArmCalcAJFromYCoord(float y, float uaAngle);
float ArmCalcAJFromXCoord(float x, float uaAngle);
float ArmCalcXCoord(float uaAngle, float ajAngle);
float ArmCalcYCoord(float uaAngle, float ajAngle);
void ArmMoveHorizontal(float y, float startAngle, float endAngle, float time);
void ArmMoveVertical(float x, float startAngle, float endAngle, float time);
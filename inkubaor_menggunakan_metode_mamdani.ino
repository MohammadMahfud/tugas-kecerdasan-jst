#include <Fuzzy.h>
 
Fuzzy *fuzzy = new Fuzzy();

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Instantiating a FuzzyInput object
  FuzzyInput *distance = new FuzzyInput(1);
  FuzzySet *small = new FuzzySet(0, 150, 150, 300);
  distance->addFuzzySet(small);
  FuzzySet *safe = new FuzzySet(400, 550, 550, 700);
  distance->addFuzzySet(safe);
  FuzzySet *big = new FuzzySet(750, 900, 900, 1000);
  distance->addFuzzySet(big);
  fuzzy->addFuzzyInput(distance); 

  // Instantiating a FuzzyOutput objects
  FuzzyOutput *speed = new FuzzyOutput(1);
  FuzzySet *slow = new FuzzySet(0, 0, 0, 1);
  speed->addFuzzySet(slow);
  FuzzySet *average = new FuzzySet(0, 0, 0, 1);
  speed->addFuzzySet(average);
  FuzzySet *fast = new FuzzySet(0, 0, 0, 0);
  speed->addFuzzySet(fast);
  fuzzy->addFuzzyOutput(speed);

//fuzzy_rule1
  FuzzyRuleAntecedent *ifDistanceSmall = new FuzzyRuleAntecedent();
  ifDistanceSmall->joinSingle(small);
  FuzzyRuleConsequent *thenSpeedSlow = new FuzzyRuleConsequent();
  thenSpeedSlow->addOutput(slow);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenSpeedSlow);
  fuzzy->addFuzzyRule(fuzzyRule01);

  //fuzzy_rule2
  FuzzyRuleAntecedent *ifDistanceSafe = new FuzzyRuleAntecedent();
  ifDistanceSafe->joinSingle(safe);
  FuzzyRuleConsequent *thenSpeedAverage = new FuzzyRuleConsequent(); 
  thenSpeedAverage->addOutput(average);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenSpeedAverage);
  fuzzy->addFuzzyRule(fuzzyRule02);

  //fuzzy_rule3
  FuzzyRuleAntecedent *ifDistanceBig = new FuzzyRuleAntecedent();
  ifDistanceBig->joinSingle(big);
  FuzzyRuleConsequent *thenSpeedFast = new FuzzyRuleConsequent();
  thenSpeedFast->addOutput(fast);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenSpeedFast);
  fuzzy->addFuzzyRule(fuzzyRule03);
}

void loop()
{
  
  int input = random(0, 1000);
  Serial.println("\n\n\nEntrance: ");
  Serial.print("\t\t\tDistance: ");
  Serial.println(input);

  fuzzy->setInput(1, input);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  Serial.println("Result: ");
  Serial.print("\t\t\tSpeed: ");
  Serial.println(output);

  delay(12000);
}

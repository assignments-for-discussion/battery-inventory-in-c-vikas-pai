#include <stdio.h>
#include <assert.h>

struct CountsBySoH
{
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int *presentCapacities, int nBatteries)
{
  struct CountsBySoH counts = {0, 0, 0};
  if (nBatteries == 0)
  {
    // Handle empty array
    return counts;
  }
  // Iterate over all batteries
  for (int i = 0; i < nBatteries; i++)
  {
    // Calculate state of health (SoH) as a percentage of the original capacity
    if (presentCapacities[i] < 0 || presentCapacities[i] > 120)
    {
      // Handle invalid capacity
      // skip the current iteration
      printf("Invalid capacity: %d\n", presentCapacities[i]);
      continue;
    }
    // Computing SoH
    float soh = 100 * (float)presentCapacities[i] / 120.0;
    printf("SoH of Battery %d is: %f\n", i,soh);
    if (soh > 80.0)
    {
      // Healthy batteries have SoH >= 80%
      counts.healthy++;
    }
    else if (soh >= 62.0)
    {
      // Batteries for exchange have 62% <= SoH < 82%
      counts.exchange++;
    }
    else
    {
      // Failed batteries have SoH < 62%
      counts.failed++;
    }
  }
  return counts;
}

void testBucketingByHealth()
{
  const int presentCapacities[] = {113, 116, 80, 95, 92, 70, -1, 121};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by SoH...\n");
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  printf("Done counting :)\n");
}

int main()
{
  testBucketingByHealth();
  return 0;
}
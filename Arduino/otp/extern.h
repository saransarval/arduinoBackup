extern unsigned int led;
extern void delaysec(void);

void delaysec(void)
{
  for(led=0;led<1000;led++)
  {}
}


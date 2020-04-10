unsigned char read_touch()
{
   unsigned char array[15]={0}, pre_count=0, pre_value=0, count=0, i, j, x_value=0, y_value=0;
   
   for(i=0; i<15; i++)
   {
      trisa=0x05;
      TOUCH_Y1=0;
      TOUCH_Y2=1;
      
      adcon0=0x81;
      adcon1=0x42;
      
      delay_ms(10);
      go=1;
      delay_ms(1);
      while(go);
      array[i]=adresh;
   }

    for(i=0;i<14;i++)
   {
      for(j=i,count=0;j<14;j++)
      {
         //if(array[i]==array[j])
         if(((array[i]-array[j])<5) || ((array[j]-array[i])<5))
         {
            count++;
            if(j==13)
            {
               if(pre_count<count)
               {
                  pre_count=count;
                  pre_value=array[i];
               }
            }
         }
      }
    
     if(pre_count>10)
      x_value=pre_value;
      
     else
      x_value=0;
   }
   
   pre_count=0;
   
   ///////////////////// Y VALUE /////////////////
   
   for(i=0; i<15; i++)
   {
      trisa=0x22;
      TOUCH_X1=0;
      TOUCH_X2=1;
      
      adcon0=0x89;
      adcon1=0x42;
      
      delay_ms(10);
      go=1;
      delay_ms(1);
      while(go);
      array[i]=adresh;
   }
   
   
   for(i=0;i<14;i++)
   {
      for(j=i,count=0;j<14;j++)
      {
         //if(array[i]==array[j])
         if(((array[i]-array[j])<5) || ((array[j]-array[i])<5))
         {
            count++;
            if(j==13)
            {
               if(pre_count<count)
               {
                  pre_count=count;
                  pre_value=array[i];
               }
            }
         }
      }
    
     if(pre_count>10)
      y_value=pre_value;
      
     else
      y_value=0;
   }
   x_value=x_value/26;
   y_value=y_value/26;
   
  // return ((x_value & 0xf0)|((y_value>>8) & 0x0f));
  
  return ((x_value*10)+(y_value));
   
}


void setup()
{
  size(300,300);
  
  background(255);
  stroke(0);
}
 
 
void draw()
{
  if(millis() % 1000 > 500)
    fill(255,0,0);
  else
    fill(0,255,0);
    
  rect(20,20,260,260);
}
 

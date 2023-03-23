PImage I, Iiv;

void setup(){
  size(512, 512);
  background(0);
  I = loadImage("lena.png");
  
  Iiv = wow(I);
  
  image(Iiv, 0, 0);
}

void draw(){
}

PImage wow(PImage Im){
  PImage R = Im.copy();
  float r, g, b;
  float f = random(0, 2);
  for(int x = 0; x < Im.width; x++){
     for(int y = 0; y < Im.height; y++){
       if(x > 0 && x < width/3){
         R.set(x, y, Im.get(x+(width-(width/3)), y));
       }
       if(x > (width-(width/3)) && x < width){
         R.set(x, y, Im.get(x-(width-(width/3)), y));
       }
     }
  }
  
  for(int x = 0; x < Im.width; x++){
     for(int y = 0; y < Im.height; y++){
         r = red(R.get(x, y)); 
         g = green(R.get(x, y));
         b = blue(R.get(x, y));
         if(x > 0 && x < width/3){
           R.set(x, y, color(r/f, g, b));
         }
         if(x > (width-(width/3)) && x < width){
           R.set(x, y, color(r*f, g, b));
         }
     }
  }
  return R;
}

void keyPressed(){
  if(key == 'r' || key == 'R'){
    Iiv = wow(I);
  }
  image(Iiv, 0, 0);
}

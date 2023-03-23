PImage im;
void setup(){
 size(512,256); 
 im=loadImage("lena.jpg");
 im.resize(256,256);
 image(im, 0, 0);
 image(inverti(im), 256, 0);
}

void draw(){}

PImage inverti(PImage i){
  PImage R = i.copy();
  PImage sx, dx;
  sx=R.get(0,0,R.width/2,R.height);
  dx=R.get(R.width/2,0,R.width/2,R.height);
  
  R.set(0,0,dx);
  R.set(R.width/2,0,sx);
  return wow(R);
}

PImage wow(PImage I){
  int r = round(random(0,100));
  PImage temp;
  PImage im = createImage(I.width, I.height, RGB);
  color c;
  temp = I.get(0,0, I.width/2, I.height);
  im.set(128,0,temp);
  temp = I.get(128,0, I.width/2, I.height);
  im.set(0,0,temp);
  
    for(int x = 0; x < im.width; x++){
      for(int y = 0; y < im.height; y++){
        c = I.get(x,y);
          if(y<I.width*r/100){
            im.set(x,y,color(blue(c),green(c),red(c)));
          }else{
            im.set(x,y,color(red(c),blue(c),green(c)));
          }
      }
    }
  return im;
}

void keyPressed(){
  if(key == 'r' || key == 'R')
    setup();
}

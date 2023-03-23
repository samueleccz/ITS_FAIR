class MegaSmile extends Smile{
color c;
MegaSmile(int posx1, int posy1, int velx1){
  super(posx1, posy1, velx1);
  c = color(255,255,255);
}

void move(){
  posx = posx-velx;
}

void display(){
  stroke(c);
  strokeWeight(2);
  noFill(); 
  pushMatrix();
  translate(posx,posy);
  scale(1.5);
  ellipse(10, 10, diam, diam);
  line(0, -5, 0, 10);
  line(20, -5, 20, 10);
  line(0, 20, 20, 20);
  popMatrix();
}

void border(){
  if(posx < 0){
    posx=500;
  }
}  

void run(){
  border();
  move();
  display();
}

}

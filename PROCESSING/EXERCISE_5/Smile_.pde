class Smile{
int posx, posy, velx, diam=50;
color c;

Smile(int posx1, int posy1, int velx1){
  posx = posx1;
  posy = posy1;
  velx = velx1;
  c=color(255, 255, 0);
}

void move(){
  posx += velx;
}

void display(){
  stroke(c);
  strokeWeight(2);
  noFill();
  ellipse(posx, posy, diam, diam);
  line(posx-10, posy-5, posx-10, posy-15);
  line(posx+10, posy-5, posx+10, posy-15);
  line(posx-10, posy+10, posx+10, posy+10);
}

void border(){
  if(posx > 500 || posx < 0){
    velx=-velx;
  }
}

void run(){
  border();
  move();
  display();
}

}

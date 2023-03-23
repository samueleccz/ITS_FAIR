class Voto{
  int posx, posy, velx, lato=30, vote;
  color c;

  Voto(int posx1, int posy1, int velx1, int vote1){
    posx = posx1;
    posy = posy1;
    velx = velx1;
    vote = vote1;
    c=color(255, 204, 0);
  }

void move(){
  posx += velx;
}

void display(){
  stroke(c);
  strokeWeight(2);
  noFill();
  rect(posx, posy, lato, lato);
  textSize(28);
  text(str(vote), posx-(lato/15), posy+(lato));
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

class Votone extends Voto{
  color c;
  Votone(int posx,int posy,int velx1, int vote1){
    super(posx, posy, velx1, vote1);
    c = color(255,255,255);
  }


void display(){

    if(vote > 24){
    text("LODE", posy, posx);
    }else{
     stroke(c);
     strokeWeight(2);
     noFill();
    rect(posx, posy, lato, lato);
    text(str(vote), posx-(lato/15), posy+(lato));
    }
}

void run(){
  display();
}

}

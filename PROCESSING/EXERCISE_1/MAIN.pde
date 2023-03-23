ArrayList<Voto> v;
ArrayList<Votone> V;

void setup(){
  size(500, 500);
  background(0);
  v = new ArrayList<Voto>();
  V = new ArrayList<Votone>();
}

void draw(){
    background(0);
  for(Voto i:v)
    i.run();
  for(Votone j:V)
    j.run();
}


void mouseClicked(){
  if(mouseButton == LEFT)
    v.add(new Voto(int(random(0, 501)), int(random(0, 501)), int(random(2,10)), int(random(18,30)) ));
  if(mouseButton == RIGHT){
    V.add(new Votone(int(random(0, 501)), int(random(0, 501)), int(random(2,10)), int(random(18,30))));
  }
}

void keyPressed() {
  if (key=='r' || key=='R') {
    setup();
  }
}

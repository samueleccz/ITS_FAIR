ArrayList<Smile> s;
ArrayList<MegaSmile> S;

void setup(){
  size(500, 500);
  background(0);
  s = new ArrayList<Smile>();
  S = new ArrayList<MegaSmile>();
}

void draw(){
  background(0);
  for(Smile i:s)
    i.run();
  for(MegaSmile j:S)
    j.run();
}

void mouseClicked(){
  if(mouseButton == LEFT)
    s.add(new Smile(int(random(0, 501)), int(random(0, 501)), int(random(1,12))));
  if(mouseButton == RIGHT){
    S.add(new MegaSmile(int(random(0, 501)), int(random(0, 501)), int(random(1,12))));
  }
}

void keyPressed() {
  if (key=='r') {
    setup();
  }
}

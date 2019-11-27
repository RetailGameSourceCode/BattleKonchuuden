ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
JAPAN_DIR=ckbt\rsd
JPTOB_DIR=58tob\rsd

all : ck1.mod ck2.mod
    psymake

ck1.mod: $(JAPAN_DIR)\ck1.lz $(JPTOB_DIR)\cktob1.lz
	hdlink /n /l ck1.lis

$(JAPAN_DIR)\ck1.lz:
	cd $(JAPAN_DIR)
	rsdlink jpnomal.arg
	tmdsort -o ck1.tmd a.tmd
	cmplz ck1.tmd ck1.lz
	del a.tmd
	cd ..\..

$(JPTOB_DIR)\cktob1.lz:
	cd $(JPTOB_DIR)
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name58.tim     896   0   0 487
	timpos $(NAMEVS)/namevs58.tim 896  16  16 487
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name58.tim     name.lz
	cmplz $(NAMEVS)/namevs58.tim namevs.lz
	hdlink /n /l ..\..\ck1t.lis
	rsdlink jptob.arg
	tmdsort -o cktob1.tmd a.tmd
	cmplz cktob1.tmd cktob1.lz
	del a.tmd
	cd ..\..

ck2.mod: $(JAPAN_DIR)\ck2.lz $(JPTOB_DIR)\cktob2.lz
	hdlink /n /l ck2.lis

$(JAPAN_DIR)\ck2.lz:
	cd $(JAPAN_DIR)
	rsdlink jpnomal.arg
	tmdsort -o ck2.tmd a.tmd
	cmplz ck2.tmd ck2.lz
	del a.tmd
	cd ..\..

$(JPTOB_DIR)\cktob2.lz:
	cd $(JPTOB_DIR)
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name58.tim     926   0   0 495
	timpos $(NAMEVS)/namevs58.tim 896  56  16 495
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name58.tim     name.lz
	cmplz $(NAMEVS)/namevs58.tim namevs.lz
	hdlink /n /l ..\..\ck2t.lis
	rsdlink jptob.arg
	tmdsort -o cktob2.tmd a.tmd
	cmplz cktob2.tmd cktob2.lz
	del a.tmd
	cd ..\..


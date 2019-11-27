ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=44\rsd
RSDTOB_DIR=44tob\rsd

all : tk.mot tk1.mod tk2.mod
    psymake

tk1.mod: $(RSD_DIR)\tk1.lz $(RSDTOB_DIR)\tktob1.lz
	hdlink /n /l tk1.lis

$(RSD_DIR)\tk1.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/hane2.tim   448   0  16 482
	timpos $(TIM_DIR)/hane1.tim   448  56  32 482
	timpos $(TIM_DIR)/asi.tim     448 112  48 482
	timpos $(TIM_DIR)/me.tim      462  56  64 482
	timpos $(TIM_DIR)/hara4.tim   472   0  80 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name44.tim     896   0   0 487
	timpos $(NAMEVS)/namevs44.tim 896  16  16 487
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/asi.tim     asi.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name44.tim     name.lz
	cmplz $(NAMEVS)/namevs44.tim namevs.lz
	hdlink /n /l ..\..\tk1t.lis
	rsdlink tnkw.arg
	tmdsort -o tk1.tmd a.tmd
	cmplz tk1.tmd tk1.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\tktob1.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/hane2.tim   448   0  16 482
	timpos $(TIM_DIR)/hane1.tim   448  56  32 482
	timpos $(TIM_DIR)/asi.tim     448 112  48 482
	timpos $(TIM_DIR)/me.tim      462  56  64 482
	timpos $(TIM_DIR)/hara4.tim   472   0  80 482
	rsdlink 44tob.arg
	tmdsort -o tktob1.tmd a.tmd
	cmplz tktob1.tmd tktob1.lz
	del a.tmd
	cd ..\..

tk2.mod: $(RSD_DIR)\tk2.lz $(RSDTOB_DIR)\tktob2.lz
	hdlink /n /l tk2.lis

$(RSD_DIR)\tk2.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/hane2.tim   704   0  16 490
	timpos $(TIM_DIR)/hane1.tim   704  56  32 490
	timpos $(TIM_DIR)/asi.tim     704 112  48 490
	timpos $(TIM_DIR)/me.tim      718  56  64 490
	timpos $(TIM_DIR)/hara4.tim   728   0  80 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name44.tim     926   0   0 495
	timpos $(NAMEVS)/namevs44.tim 896  56  16 495
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/asi.tim     asi.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name44.tim     name.lz
	cmplz $(NAMEVS)/namevs44.tim namevs.lz
	hdlink /n /l ..\..\tk2t.lis
	rsdlink tnkw.arg
	tmdsort -o tk2.tmd a.tmd
	cmplz tk2.tmd tk2.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\tktob2.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/hane2.tim   704   0  16 490
	timpos $(TIM_DIR)/hane1.tim   704  56  32 490
	timpos $(TIM_DIR)/asi.tim     704 112  48 490
	timpos $(TIM_DIR)/me.tim      718  56  64 490
	timpos $(TIM_DIR)/hara4.tim   728   0  80 490
	rsdlink 44tob.arg
	tmdsort -o tktob2.tmd a.tmd
	cmplz tktob2.tmd tktob2.lz
	del a.tmd
	cd ..\..

tk.mot:
	hdlink /n /l tk.lis




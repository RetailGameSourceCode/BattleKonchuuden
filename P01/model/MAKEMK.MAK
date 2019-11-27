ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
MECHA_DIR=01roboa\rsd
MECTOB_DIR=01robtob\rsd

all : mk1.mod mk2.mod
    psymake

mk1.mod: $(MECHA_DIR)\mk1.lz $(MECTOB_DIR)\mktob1.lz
	hdlink /n /l mk1.lis

$(MECHA_DIR)\mk1.lz:
	cd $(MECHA_DIR)
	timpos $(TIM_DIR)/head.tim    320   0  16 482
	timpos $(TIM_DIR)/ura.tim     384   0  32 482
	timpos $(TIM_DIR)/body2.tim   448   0  48 482
	timpos $(TIM_DIR)/cover.tim   448  48  64 482
	timpos $(TIM_DIR)/body.tim    448  96  80 482
	timpos $(TIM_DIR)/tuuki.tim   448 144  96 482
	timpos $(TIM_DIR)/gun.tim     448 192 112 482
	timpos $(TIM_DIR)/helmet.tim  448 224 144 482
	timpos $(TIM_DIR)/helmet2.tim 456 192 160 482
	timpos $(TIM_DIR)/neck.tim    456 224 176 482
	timpos $(TIM_DIR)/face.tim    460   0 192 482
	timpos $(TIM_DIR)/ironman.tim 512   0 128 482
	rsdlink jpnomal.arg
	tmdsort -o mk1.tmd a.tmd
	cmplz mk1.tmd mk1.lz
	del a.tmd
	cd ..\..

$(MECTOB_DIR)\mktob1.lz:
	cd $(MECTOB_DIR)
	timpos $(TIM_DIR)/head.tim    320   0  16 482
	timpos $(TIM_DIR)/ura.tim     384   0  32 482
	timpos $(TIM_DIR)/body2.tim   448   0  48 482
	timpos $(TIM_DIR)/cover.tim   448  48  64 482
	timpos $(TIM_DIR)/body.tim    448  96  80 482
	timpos $(TIM_DIR)/tuuki.tim   448 144  96 482
	timpos $(TIM_DIR)/gun.tim     448 192 112 482
	timpos $(TIM_DIR)/helmet.tim  448 224 144 482
	timpos $(TIM_DIR)/helmet2.tim 456 192 160 482
	timpos $(TIM_DIR)/neck.tim    456 224 176 482
	timpos $(TIM_DIR)/face.tim    460   0 192 482
	timpos $(TIM_DIR)/hane.tim    476   0 208 482
	timpos $(TIM_DIR)/ironman.tim 512   0 128 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name55.tim      896   0   0 487
	timpos $(NAMEVS)/namevs55.tim  896  16  16 487
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ura.tim     ura.lz
	cmplz $(TIM_DIR)/body2.tim   body2.lz
	cmplz $(TIM_DIR)/cover.tim   cover.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/tuuki.tim   tuuki.lz
	cmplz $(TIM_DIR)/gun.tim     gun.lz
	cmplz $(TIM_DIR)/helmet.tim  helmet.lz
	cmplz $(TIM_DIR)/helmet2.tim helmet2.lz
	cmplz $(TIM_DIR)/neck.tim    neck.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/ironman.tim ironman.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name55.tim      name.lz
	cmplz $(NAMEVS)/namevs55.tim  namevs.lz
	hdlink /n /l ..\..\mk1t.lis
	rsdlink jptob.arg
	tmdsort -o mktob1.tmd a.tmd
	cmplz mktob1.tmd mktob1.lz
	del a.tmd
	cd ..\..

mk2.mod: $(MECHA_DIR)\mk2.lz $(MECTOB_DIR)\mktob2.lz
	hdlink /n /l mk2.lis

$(MECHA_DIR)\mk2.lz:
	cd $(MECHA_DIR)
	timpos $(TIM_DIR)/head.tim    576   0  16 490
	timpos $(TIM_DIR)/ura.tim     640   0  32 490
	timpos $(TIM_DIR)/body2.tim   704   0  48 490
	timpos $(TIM_DIR)/cover.tim   704  48  64 490
	timpos $(TIM_DIR)/body.tim    704  96  80 490
	timpos $(TIM_DIR)/tuuki.tim   704 144  96 490
	timpos $(TIM_DIR)/gun.tim     704 192 112 490
	timpos $(TIM_DIR)/helmet.tim  704 224 144 490
	timpos $(TIM_DIR)/helmet2.tim 712 192 160 490
	timpos $(TIM_DIR)/neck.tim    712 224 176 490
	timpos $(TIM_DIR)/face.tim    716   0 192 490
	timpos $(TIM_DIR)/ironman.tim 768   0 128 490
	rsdlink jpnomal.arg
	tmdsort -o mk2.tmd a.tmd
	cmplz mk2.tmd mk2.lz
	del a.tmd
	cd ..\..

$(MECTOB_DIR)\mktob2.lz:
	cd $(MECTOB_DIR)
	timpos $(TIM_DIR)/head.tim    576   0  16 490
	timpos $(TIM_DIR)/ura.tim     640   0  32 490
	timpos $(TIM_DIR)/body2.tim   704   0  48 490
	timpos $(TIM_DIR)/cover.tim   704  48  64 490
	timpos $(TIM_DIR)/body.tim    704  96  80 490
	timpos $(TIM_DIR)/tuuki.tim   704 144  96 490
	timpos $(TIM_DIR)/gun.tim     704 192 112 490
	timpos $(TIM_DIR)/helmet.tim  704 224 144 490
	timpos $(TIM_DIR)/helmet2.tim 712 192 160 490
	timpos $(TIM_DIR)/neck.tim    712 224 176 490
	timpos $(TIM_DIR)/face.tim    716   0 192 490
	timpos $(TIM_DIR)/hane.tim    732   0 208 490
	timpos $(TIM_DIR)/ironman.tim 768   0 128 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name55.tim      926   0   0 495
	timpos $(NAMEVS)/namevs55.tim  896  56  16 495
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ura.tim     ura.lz
	cmplz $(TIM_DIR)/body2.tim   body2.lz
	cmplz $(TIM_DIR)/cover.tim   cover.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/tuuki.tim   tuuki.lz
	cmplz $(TIM_DIR)/gun.tim     gun.lz
	cmplz $(TIM_DIR)/helmet.tim  helmet.lz
	cmplz $(TIM_DIR)/helmet2.tim helmet2.lz
	cmplz $(TIM_DIR)/neck.tim    neck.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/ironman.tim ironman.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name55.tim      name.lz
	cmplz $(NAMEVS)/namevs55.tim  namevs.lz
	hdlink /n /l ..\..\mk2t.lis
	rsdlink jptob.arg
	tmdsort -o mktob2.tmd a.tmd
	cmplz mktob2.tmd mktob2.lz
	del a.tmd
	cd ..\..


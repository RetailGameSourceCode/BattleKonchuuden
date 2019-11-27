ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KBT_DIR=02bokan\rsd
TOBI_DIR=02boktob\rsd

all : me1.mod me2.mod
    psymake

me1.mod: $(KBT_DIR)/me1.lz $(TOBI_DIR)/me01.lz
	hdlink /n /l me1.lis

$(KBT_DIR)/me1.lz:
	cd $(KBT_DIR)
	timpos $(TIM_DIR)/head.tim    320   0  16 482
	timpos $(TIM_DIR)/ura.tim     320 128  32 482
	timpos $(TIM_DIR)/ura2.tim    352   0  48 482
	timpos $(TIM_DIR)/j.tim       352 128  64 482
	timpos $(TIM_DIR)/line.tim    384   0   0 480
	timpos $(TIM_DIR)/body3.tim   384  32  80 482
	timpos $(TIM_DIR)/body.tim    384  96  96 482
	timpos $(TIM_DIR)/body2.tim   384 160 112 482
	timpos $(TIM_DIR)/ten.tim     384 224 128 482
	timpos $(TIM_DIR)/line2.tim   392 224 144 482
	timpos $(TIM_DIR)/body4.tim   400  32 160 482
	timpos $(TIM_DIR)/ten2.tim    400  96 176 482
	timpos $(TIM_DIR)/me1.tim     400 112 192 482
	timpos $(TIM_DIR)/me2.tim     400 128 208 482
	timpos $(TIM_DIR)/tuuki.tim   464   0  32 491
	rsdlink iki.arg
	tmdsort -o me1.tmd a.tmd
	cmplz me1.tmd me1.lz
	del a.tmd
	cd ..\..

$(TOBI_DIR)/me01.lz:
	cd $(TOBI_DIR)
	timpos $(TIM_DIR)/head.tim    320   0  16 482
	timpos $(TIM_DIR)/ura.tim     320 128  32 482
	timpos $(TIM_DIR)/ura2.tim    352   0  48 482
	timpos $(TIM_DIR)/j.tim       352 128  64 482
	timpos $(TIM_DIR)/line.tim    384   0   0 480
	timpos $(TIM_DIR)/body3.tim   384  32  80 482
	timpos $(TIM_DIR)/body.tim    384  96  96 482
	timpos $(TIM_DIR)/body2.tim   384 160 112 482
	timpos $(TIM_DIR)/ten.tim     384 224 128 482
	timpos $(TIM_DIR)/line2.tim   392 224 144 482
	timpos $(TIM_DIR)/body4.tim   400  32 160 482
	timpos $(TIM_DIR)/ten2.tim    400  96 176 482
	timpos $(TIM_DIR)/me1.tim     400 112 192 482
	timpos $(TIM_DIR)/me2.tim     400 128 208 482
	timpos $(TIM_DIR)/hane.tim   448   0   0 481
	timpos $(TIM_DIR)/red.tim     448  64 224 482
	timpos $(TIM_DIR)/silver.tim  448 128 240 482
	timpos $(TIM_DIR)/engine.tim  448 192   0 483
	timpos $(TIM_DIR)/tuuki.tim   464   0  32 491
	timpos $(TIM_DIR)/blue.tim    464  64  16 483
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name56.tim     896   0   0 487
	timpos $(NAMEVS)/namevs56.tim 896  16  16 487
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ura.tim     ura.lz
	cmplz $(TIM_DIR)/ura2.tim    ura2.lz
	cmplz $(TIM_DIR)/j.tim       j.lz
	cmplz $(TIM_DIR)/line.tim    line.lz
	cmplz $(TIM_DIR)/body3.tim   body3.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/body2.tim   body2.lz
	cmplz $(TIM_DIR)/ten.tim     ten.lz
	cmplz $(TIM_DIR)/line2.tim   line2.lz
	cmplz $(TIM_DIR)/body4.tim   body4.lz
	cmplz $(TIM_DIR)/ten2.tim    ten2.lz
	cmplz $(TIM_DIR)/me1.tim     me1.lz
	cmplz $(TIM_DIR)/me2.tim     me2.lz
	cmplz $(TIM_DIR)/hane.tim   hane.lz
	cmplz $(TIM_DIR)/red.tim     red.lz
	cmplz $(TIM_DIR)/silver.tim  silver.lz
	cmplz $(TIM_DIR)/engine.tim  engine.lz
	cmplz $(TIM_DIR)/tuuki.tim   tuuki.lz
	cmplz $(TIM_DIR)/blue.tim    blue.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name56.tim     name.lz
	cmplz $(NAMEVS)/namevs56.tim namevs.lz
	hdlink /n /l ..\..\me1t.lis
	rsdlink hr.arg
	tmdsort -o me01.tmd a.tmd
	cmplz me01.tmd me01.lz
	del a.tmd
	cd ..\..

me2.mod: $(KBT_DIR)/me2.lz $(TOBI_DIR)/me02.lz
	hdlink /n /l me2.lis

$(KBT_DIR)/me2.lz:
	cd $(KBT_DIR)
	timpos $(TIM_DIR)/head.tim    576   0  16 490
	timpos $(TIM_DIR)/ura.tim     576 128  32 490
	timpos $(TIM_DIR)/ura2.tim    608   0  48 490
	timpos $(TIM_DIR)/j.tim       608 128  64 490
	timpos $(TIM_DIR)/line.tim    640   0   0 488
	timpos $(TIM_DIR)/body3.tim   640  32  80 490
	timpos $(TIM_DIR)/body.tim    640  96  96 490
	timpos $(TIM_DIR)/body2.tim   640 160 112 490
	timpos $(TIM_DIR)/ten.tim     640 224 128 490
	timpos $(TIM_DIR)/line2.tim   648 224 144 490
	timpos $(TIM_DIR)/body4.tim   656  32 160 490
	timpos $(TIM_DIR)/ten2.tim    656  96 176 490
	timpos $(TIM_DIR)/me1.tim     656 112 192 490
	timpos $(TIM_DIR)/me2.tim     656 128 208 490
	timpos $(TIM_DIR)/tuuki.tim   720   0  32 491
	rsdlink iki.arg
	tmdsort -o me2.tmd a.tmd
	cmplz me2.tmd me2.lz
	del a.tmd
	cd ..\..

$(TOBI_DIR)/me02.lz:
	cd $(TOBI_DIR)
	timpos $(TIM_DIR)/head.tim    576   0  16 490
	timpos $(TIM_DIR)/ura.tim     576 128  32 490
	timpos $(TIM_DIR)/ura2.tim    608   0  48 490
	timpos $(TIM_DIR)/j.tim       608 128  64 490
	timpos $(TIM_DIR)/line.tim    640   0   0 488
	timpos $(TIM_DIR)/body3.tim   640  32  80 490
	timpos $(TIM_DIR)/body.tim    640  96  96 490
	timpos $(TIM_DIR)/body2.tim   640 160 112 490
	timpos $(TIM_DIR)/ten.tim     640 224 128 490
	timpos $(TIM_DIR)/line2.tim   648 224 144 490
	timpos $(TIM_DIR)/body4.tim   656  32 160 490
	timpos $(TIM_DIR)/ten2.tim    656  96 176 490
	timpos $(TIM_DIR)/me1.tim     656 112 192 490
	timpos $(TIM_DIR)/me2.tim     656 128 208 490
	timpos $(TIM_DIR)/hane.tim   704   0   0 489
	timpos $(TIM_DIR)/red.tim     704  64 224 490
	timpos $(TIM_DIR)/silver.tim  704 128 240 490
	timpos $(TIM_DIR)/engine.tim  704 192   0 491
	timpos $(TIM_DIR)/tuuki.tim   720   0  32 491
	timpos $(TIM_DIR)/blue.tim    720  64  16 491
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name56.tim     926   0   0 495
	timpos $(NAMEVS)/namevs56.tim 896  56  16 495
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ura.tim     ura.lz
	cmplz $(TIM_DIR)/ura2.tim    ura2.lz
	cmplz $(TIM_DIR)/j.tim       j.lz
	cmplz $(TIM_DIR)/line.tim    line.lz
	cmplz $(TIM_DIR)/body3.tim   body3.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/body2.tim   body2.lz
	cmplz $(TIM_DIR)/ten.tim     ten.lz
	cmplz $(TIM_DIR)/line2.tim   line2.lz
	cmplz $(TIM_DIR)/body4.tim   body4.lz
	cmplz $(TIM_DIR)/ten2.tim    ten2.lz
	cmplz $(TIM_DIR)/me1.tim     me1.lz
	cmplz $(TIM_DIR)/me2.tim     me2.lz
	cmplz $(TIM_DIR)/hane.tim   hane.lz
	cmplz $(TIM_DIR)/red.tim     red.lz
	cmplz $(TIM_DIR)/silver.tim  silver.lz
	cmplz $(TIM_DIR)/engine.tim  engine.lz
	cmplz $(TIM_DIR)/tuuki.tim   tuuki.lz
	cmplz $(TIM_DIR)/blue.tim    blue.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name56.tim     name.lz
	cmplz $(NAMEVS)/namevs56.tim namevs.lz
	hdlink /n /l ..\..\me2t.lis
	rsdlink hr.arg
	tmdsort -o me02.tmd a.tmd
	cmplz me02.tmd me02.lz
	del a.tmd
	cd ..\..


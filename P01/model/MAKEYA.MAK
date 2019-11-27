ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
YANUS_DIR=09\rsd
YATOB_DIR=09tob\rsd

all : ya.mot ya1.mod ya2.mod
    psymake

ya1.mod: $(YANUS_DIR)\ya1.lz $(YATOB_DIR)\yatob1.lz
	hdlink /n /l ya1.lis

$(YANUS_DIR)\ya1.lz:
	cd $(YANUS_DIR)
	timpos $(TIM_DIR)/hara2.tim   320   0  96 482
	timpos $(TIM_DIR)/hara1.tim   320  72  80 482
	timpos $(TIM_DIR)/hane2.tim   358   0  48 482
	timpos $(TIM_DIR)/hara3.tim   358  56  32 482
	timpos $(TIM_DIR)/athane.tim  384   0   0 480
	timpos $(TIM_DIR)/me.tim      488 128 112 482
	timpos $(TIM_DIR)/syokaku.tim 488 184 128 482
	timpos $(TIM_DIR)/head.tim    512   0  16 482
	timpos $(TIM_DIR)/hane1.tim   548   0  64 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name9.tim      896   0   0 487
	timpos $(NAMEVS)/namevs9.tim  896  16  16 487
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name9.tim      name.lz
	cmplz $(NAMEVS)/namevs9.tim  namevs.lz
	hdlink /n /l ..\..\ya1t.lis
	rsdlink yaiki.arg
	tmdsort -o ya1.tmd a.tmd
	cmplz ya1.tmd ya1.lz
	del a.tmd
	cd ..\..

$(YATOB_DIR)\yatob1.lz:
	cd $(YATOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   320   0  96 482
	timpos $(TIM_DIR)/hara1.tim   320  72  80 482
	timpos $(TIM_DIR)/hane2.tim   358   0  48 482
	timpos $(TIM_DIR)/hara3.tim   358  56  32 482
	timpos $(TIM_DIR)/athane.tim  384   0   0 480
	timpos $(TIM_DIR)/me.tim      488 128 112 482
	timpos $(TIM_DIR)/syokaku.tim 488 184 128 482
	timpos $(TIM_DIR)/head.tim    512   0  16 482
	timpos $(TIM_DIR)/hane1.tim   548   0  64 482
	rsdlink yztob.arg
	tmdsort -o yatob1.tmd a.tmd
	cmplz yatob1.tmd yatob1.lz
	del a.tmd
	cd ..\..

ya2.mod: $(YANUS_DIR)\ya2.lz $(YATOB_DIR)\yatob2.lz
	hdlink /n /l ya2.lis

$(YANUS_DIR)\ya2.lz:
	cd $(YANUS_DIR)
	timpos $(TIM_DIR)/hara2.tim   576   0  96 490
	timpos $(TIM_DIR)/hara1.tim   576  72  80 490
	timpos $(TIM_DIR)/hane2.tim   614   0  48 490
	timpos $(TIM_DIR)/hara3.tim   614  56  32 490
	timpos $(TIM_DIR)/athane.tim  640   0   0 488
	timpos $(TIM_DIR)/me.tim      744 128 112 490
	timpos $(TIM_DIR)/syokaku.tim 744 184 128 490
	timpos $(TIM_DIR)/head.tim    768   0  16 490
	timpos $(TIM_DIR)/hane1.tim   804   0  64 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name9.tim      926   0   0 495
	timpos $(NAMEVS)/namevs9.tim  896  56  16 495
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name9.tim      name.lz
	cmplz $(NAMEVS)/namevs9.tim  namevs.lz
	hdlink /n /l ..\..\ya2t.lis
	rsdlink yaiki.arg
	tmdsort -o ya2.tmd a.tmd
	cmplz ya2.tmd ya2.lz
	del a.tmd
	cd ..\..

$(YATOB_DIR)\yatob2.lz:
	cd $(YATOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   576   0  96 490
	timpos $(TIM_DIR)/hara1.tim   576  72  80 490
	timpos $(TIM_DIR)/hane2.tim   614   0  48 490
	timpos $(TIM_DIR)/hara3.tim   614  56  32 490
	timpos $(TIM_DIR)/athane.tim  640   0   0 488
	timpos $(TIM_DIR)/me.tim      744 128 112 490
	timpos $(TIM_DIR)/syokaku.tim 744 184 128 490
	timpos $(TIM_DIR)/head.tim    768   0  16 490
	timpos $(TIM_DIR)/hane1.tim   804   0  64 490
	rsdlink yztob.arg
	tmdsort -o yatob2.tmd a.tmd
	cmplz yatob2.tmd yatob2.lz
	del a.tmd
	cd ..\..

ya.mot: $(YANUS_DIR)\$(ANM_DIR)/yaiki.lz
	hdlink /n /l ya.lis

$(YANUS_DIR)\$(ANM_DIR)/yaiki.lz:
	cd $(YANUS_DIR)\$(ANM_DIR)
	bin2mtn yaiki
	cmplz yaiki.mtn yaiki.lz
	cd ..\..



ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
HIME_DIR=15\rsd
HIMETOB_DIR=15tob\rsd

all : hk.mot hk1.mod hk2.mod
    psymake

hk1.mod: $(HIME_DIR)\hk1.lz $(HIMETOB_DIR)\hktob1.lz
	hdlink /n /l hk1.lis

$(HIME_DIR)\hk1.lz:
	cd $(HIME_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0   0 480
	timpos $(TIM_DIR)/hane2.tim   424   0  32 482
	timpos $(TIM_DIR)/hane1.tim   424  56  64 482
	timpos $(TIM_DIR)/hara1.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448 160  48 482
	timpos $(TIM_DIR)/me.tim      502   0  80 482
	timpos $(TIM_DIR)/tuno.tim    504 112  96 482
	timpos $(TIM_DIR)/head.tim    512   0 112 482
	timpos $(TIM_DIR)/hige.tim    512 112 128 482
	timpos $(TIM_DIR)/syokaku.tim 534 136 160 482
	timpos $(TIM_DIR)/hara4.tim   556   0 176 482
	rsdlink hime.arg
	tmdsort -o hk1.tmd a.tmd
	cmplz hk1.tmd hk1.lz
	del a.tmd
	cd ..\..

$(HIMETOB_DIR)\hktob1.lz:
	cd $(HIMETOB_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0   0 480
	timpos $(TIM_DIR)/hane2.tim   424   0  32 482
	timpos $(TIM_DIR)/hane1.tim   424  56  64 482
	timpos $(TIM_DIR)/hara1.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448 160  48 482
	timpos $(TIM_DIR)/me.tim      502   0  80 482
	timpos $(TIM_DIR)/tuno.tim    504 112  96 482
	timpos $(TIM_DIR)/head.tim    512   0 112 482
	timpos $(TIM_DIR)/hige.tim    512 112 128 482
	timpos $(TIM_DIR)/syokaku.tim 534 136 160 482
	timpos $(TIM_DIR)/hara4.tim   556   0 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name15.tim     896   0   0 487
	timpos $(NAMEVS)/namevs15.tim 896  16  16 487
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name15.tim     name.lz
	cmplz $(NAMEVS)/namevs15.tim namevs.lz
	hdlink /n /l ..\..\hk1t.lis
	rsdlink 15tob.arg
	tmdsort -o hktob1.tmd a.tmd
	cmplz hktob1.tmd hktob1.lz
	del a.tmd
	cd ..\..

hk2.mod: $(HIME_DIR)\hk2.lz $(HIMETOB_DIR)\hktob2.lz
	hdlink /n /l hk2.lis

$(HIME_DIR)\hk2.lz:
	cd $(HIME_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0   0 488
	timpos $(TIM_DIR)/hane2.tim   680   0  32 490
	timpos $(TIM_DIR)/hane1.tim   680  56  64 490
	timpos $(TIM_DIR)/hara1.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704 160  48 490
	timpos $(TIM_DIR)/me.tim      758   0  80 490
	timpos $(TIM_DIR)/tuno.tim    760 112  96 490
	timpos $(TIM_DIR)/head.tim    768   0 112 490
	timpos $(TIM_DIR)/hige.tim    768 112 128 490
	timpos $(TIM_DIR)/syokaku.tim 790 136 160 490
	timpos $(TIM_DIR)/hara4.tim   812   0 176 490
	rsdlink hime.arg
	tmdsort -o hk2.tmd a.tmd
	cmplz hk2.tmd hk2.lz
	del a.tmd
	cd ..\..

$(HIMETOB_DIR)\hktob2.lz:
	cd $(HIMETOB_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0   0 488
	timpos $(TIM_DIR)/hane2.tim   680   0  32 490
	timpos $(TIM_DIR)/hane1.tim   680  56  64 490
	timpos $(TIM_DIR)/hara1.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704 160  48 490
	timpos $(TIM_DIR)/me.tim      758   0  80 490
	timpos $(TIM_DIR)/tuno.tim    760 112  96 490
	timpos $(TIM_DIR)/head.tim    768   0 112 490
	timpos $(TIM_DIR)/hige.tim    768 112 128 490
	timpos $(TIM_DIR)/syokaku.tim 790 136 160 490
	timpos $(TIM_DIR)/hara4.tim   812   0 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name15.tim     926   0   0 495
	timpos $(NAMEVS)/namevs15.tim 896  56  16 495
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name15.tim     name.lz
	cmplz $(NAMEVS)/namevs15.tim namevs.lz
	hdlink /n /l ..\..\hk2t.lis
	rsdlink 15tob.arg
	tmdsort -o hktob2.tmd a.tmd
	cmplz hktob2.tmd hktob2.lz
	del a.tmd
	cd ..\..

hk.mot: $(HIME_DIR)\$(ANM_DIR)/hkiki.lz
	hdlink /n /l hk.lis

$(HIME_DIR)\$(ANM_DIR)/hkiki.lz:
	cd $(HIME_DIR)\$(ANM_DIR)
	bin2mtn hmiki
	cmplz hmiki.mtn hkiki.lz
	cd ..\..



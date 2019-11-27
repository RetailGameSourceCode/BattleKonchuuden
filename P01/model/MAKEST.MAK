ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
SATAN_DIR=stnomal\rsd
STTOBI_DIR=stntb\rsd

all : st.mot st1.mod st2.mod
    psymake

st1.mod: $(SATAN_DIR)\st1.lz $(STTOBI_DIR)\sttobi1.lz
	hdlink /n /l st1.lis

$(SATAN_DIR)\st1.lz:
	cd $(SATAN_DIR)
	timpos $(TIM_DIR)/hara1.tim   320   0 112 482
	timpos $(TIM_DIR)/hara2.tim   320 160 144 482
	timpos $(TIM_DIR)/hige.tim    320 232 128 482
	timpos $(TIM_DIR)/body0.tim   362   0  32 482
	timpos $(TIM_DIR)/body.tim    512   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 384 144 176 482
	timpos $(TIM_DIR)/hane1.tim   400 144  96 482
	timpos $(TIM_DIR)/me.tim      420   0 160 482
	timpos $(TIM_DIR)/hane2.tim   384 200  80 482
	timpos $(TIM_DIR)/at01.tim    448   0  48 482
	timpos $(TIM_DIR)/ohige.tim   384   0  64 482
	timpos $(TIM_DIR)/hara3.tim   548   0 192 482
	rsdlink stnomal.arg
	tmdsort -o st1.tmd a.tmd
	cmplz st1.tmd st1.lz
	del a.tmd
	cd ..\..

$(STTOBI_DIR)\sttobi1.lz:
	cd $(STTOBI_DIR)
	timpos $(TIM_DIR)/hara1.tim   320   0 112 482
	timpos $(TIM_DIR)/hara2.tim   320 160 144 482
	timpos $(TIM_DIR)/hige.tim    320 232 128 482
	timpos $(TIM_DIR)/body0.tim   362   0  32 482
	timpos $(TIM_DIR)/body.tim    512   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 384 144 176 482
	timpos $(TIM_DIR)/hane1.tim   400 144  96 482
	timpos $(TIM_DIR)/me.tim      420   0 160 482
	timpos $(TIM_DIR)/hane2.tim   384 200  80 482
	timpos $(TIM_DIR)/at01.tim    448   0  48 482
	timpos $(TIM_DIR)/ohige.tim   384   0  64 482
	timpos $(TIM_DIR)/hara3.tim   548   0 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name4.tim      896   0   0 487
	timpos $(NAMEVS)/namevs4.tim  896  16  16 487
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/body0.tim   body0.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name4.tim      name.lz
	cmplz $(NAMEVS)/namevs4.tim  namevs.lz
	hdlink /n /l ..\..\st1t.lis
	rsdlink stntb.arg
	tmdsort -o sttobi1.tmd a.tmd
	cmplz sttobi1.tmd sttobi1.lz
	del a.tmd
	cd ..\..

st2.mod: $(SATAN_DIR)\st2.lz $(STTOBI_DIR)\sttobi2.lz
	hdlink /n /l st2.lis

$(SATAN_DIR)\st2.lz:
	cd $(SATAN_DIR)
	timpos $(TIM_DIR)/hara1.tim   576   0 112 490
	timpos $(TIM_DIR)/hara2.tim   576 160 144 490
	timpos $(TIM_DIR)/hige.tim    576 232 128 490
	timpos $(TIM_DIR)/body0.tim   618   0  32 490
	timpos $(TIM_DIR)/body.tim    768   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 640 144 176 490
	timpos $(TIM_DIR)/hane1.tim   656 144  96 490
	timpos $(TIM_DIR)/me.tim      676   0 160 490
	timpos $(TIM_DIR)/hane2.tim   640 200  80 490
	timpos $(TIM_DIR)/at01.tim    704   0  48 490
	timpos $(TIM_DIR)/ohige.tim   640   0  64 490
	timpos $(TIM_DIR)/hara3.tim   804   0 192 490
	rsdlink stnomal.arg
	tmdsort -o st2.tmd a.tmd
	cmplz st2.tmd st2.lz
	del a.tmd
	cd ..\..

$(STTOBI_DIR)\sttobi2.lz:
	cd $(STTOBI_DIR)
	timpos $(TIM_DIR)/hara1.tim   576   0 112 490
	timpos $(TIM_DIR)/hara2.tim   576 160 144 490
	timpos $(TIM_DIR)/hige.tim    576 232 128 490
	timpos $(TIM_DIR)/body0.tim   618   0  32 490
	timpos $(TIM_DIR)/body.tim    768   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 640 144 176 490
	timpos $(TIM_DIR)/hane1.tim   656 144  96 490
	timpos $(TIM_DIR)/me.tim      676   0 160 490
	timpos $(TIM_DIR)/hane2.tim   640 200  80 490
	timpos $(TIM_DIR)/at01.tim    704   0  48 490
	timpos $(TIM_DIR)/ohige.tim   640   0  64 490
	timpos $(TIM_DIR)/hara3.tim   804   0 192 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name4.tim      926   0   0 495
	timpos $(NAMEVS)/namevs4.tim  896  56  16 495
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/body0.tim   body0.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name4.tim      name.lz
	cmplz $(NAMEVS)/namevs4.tim  namevs.lz
	hdlink /n /l ..\..\st2t.lis
	rsdlink stntb.arg
	tmdsort -o sttobi2.tmd a.tmd
	cmplz sttobi2.tmd sttobi2.lz
	del a.tmd
	cd ..\..

st.mot: $(SATAN_DIR)\$(ANM_DIR)/stnoma.lz \
		$(STTOBI_DIR)\$(ANM_DIR)/sttob0.lz \
		$(STTOBI_DIR)\$(ANM_DIR)/sttob1.lz
	hdlink /n /l st.lis

$(SATAN_DIR)\$(ANM_DIR)/stnoma.lz:
	cd $(SATAN_DIR)\$(ANM_DIR)
	bin2mtn stnoma
	cmplz stnoma.mtn stnoma.lz
	cd ..\..

$(STTOBI_DIR)\$(ANM_DIR)/sttob0.lz:
	cd $(STTOBI_DIR)\$(ANM_DIR)
	bin2mtn sttob0
	cmplz sttob0.mtn sttob0.lz
	cd ..\..

$(STTOBI_DIR)\$(ANM_DIR)/sttob1.lz:
	cd $(STTOBI_DIR)\$(ANM_DIR)
	bin2mtn sttob1
	cmplz sttob1.mtn sttob1.lz
	cd ..\..


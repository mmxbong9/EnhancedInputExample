# Enhanced Input Example Project.
유져 입력을 통해 input binding 을 동적으로 변경하기 위함. 메뉴 호출 토클(tab)시 캐릭터의 이동 및 점프등을 제한하고 메뉴를 보여준다거나 하는 기능을 위한 샘플.

## 참고 문서.
- [Unreal Engine 5.1 Document - Enhanced Input](https://docs.unrealengine.com/5.1/ko/enhanced-input-in-unreal-engine)
- [미오29살 UE5 C++ Enhanced Input in PlayerController | 언리얼엔진5 | 01](https://youtu.be/KJyl46GWiXw)

### 기능
Tab 키 입력을 통해 임의로 지정한 Play, Menu 두가지 상태를 토글 하며, 그에 맞는 Input Binding 을 시행 함.
- UTPInputPlayData(PlayActions): ChangeMode(tab), Jump(space) Move(w,a,s,d) Look(mousepos x,y)
- UTPInputMenuData(MenuActions): Look(mousepos x,y), TogglePlayerInfo(u)

#### Play용 Input Mapping Context : IMC_Play
- 모드변경: Tab키
- 이동: w(앞)a(좌)s(뒤)d(우)
- 점프: spacebar
- 시점변경: 마우스 이동

#### Menu용 Input Mapping Context : IMC_Menu
- 모드변경: Tab키
- 시점변경: 마우스 이동
- 플레이어정보: u
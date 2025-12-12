/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "librewolf"

/* appearance */
static unsigned int borderpx   = 3;               /* border pixel of windows */
static unsigned int snap       = 32;              /* snap pixel */
static int showbar             = 1;               /* 0 means no bar */
static int topbar              = 1;               /* 0 means bottom bar */
static const int usealtbar     = 1;               /* 1 means use non-dwm status bar */
static const char *altbarclass = "Eww";            /* Alternate bar class name */
static const char *altbarcmd   = "eww open bar";  /* Alternate bar launch command */
static char secondFont[]       = "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true";
static char font[]             = "monospace:size=12";
static char dmenufont[]        = "monospace:size=12";
static const char *fonts[]     = { font, secondFont };
static char normbgcolor[]      = "#222222";
static char normbordercolor[]  = "#444444";
static char normfgcolor[]      = "#bbbbbb";
static char selfgcolor[]       = "#eeeeee";
static char selbordercolor[]   = "#005577";
static char selbgcolor[]       = "#005577";
static char titlefgcolor[]     = "#005577";
static char titlebgcolor[]     = "#005577";
static char titlebordercolor[] = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeTitle]  = { titlefgcolor, titlebgcolor, titlebordercolor }
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       tags mask     isfloating   monitor */
	{ "Gimp",       NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",    NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 2;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
  { "[][]=",    tilewide }, /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
//#define TAGKEYS(KEY,TAG) \
//	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
//	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
//	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
//	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define TAGKEYS(KEY,TAG) \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "librewolf", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",         STRING,     &font },
		{ "dmenufont",    STRING,     &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },	
		{ "titlefgcolor",         STRING,  &titlefgcolor },	
		{ "titlebgcolor",         STRING,  &titlebgcolor },	
		{ "titlebordercolor",         STRING,  &titlebordercolor },	
    { "borderpx",     INTEGER,    &borderpx },
    { "snap",         INTEGER,    &snap },
    { "usealtbar",    INTEGER,    &usealtbar },
		{ "showbar",      INTEGER,    &showbar },
		{ "topbar",       INTEGER,    &topbar },
		{ "nmaster",      INTEGER,    &nmaster },
		{ "resizehints",  INTEGER,    &resizehints },
		{ "mfact",      	FLOAT,      &mfact },
};

static const Key keys[] = {
	/* modifier                     key            function            argument */
	//{ MODKEY,			                  XK_d,		       spawn,              {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		          XK_d,		       spawn,		           {.v = (const char*[]){ "passmenu", NULL } } },
  { MODKEY,			                  XK_f,		       togglefullscr,	     {0} },
	//{ MODKEY,		 	                  XK_minus,	     spawn,		           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY|ShiftMask,		          XK_minus,	     spawn,		           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,			                  XK_equal,	     spawn,		           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY|ShiftMask,		          XK_equal,	     spawn,		           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,			                  XK_p,			     spawn,		           {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	//{ MODKEY|ShiftMask,		          XK_p,			     spawn,		           SHCMD("mpc pause;") },
	//{ MODKEY,			                  XK_comma,	     spawn,		           {.v = (const char*[]){ "mpc", "prev", NULL } } },
	//{ MODKEY|ShiftMask,		          XK_comma,	     spawn,		           {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	//{ MODKEY,			                  XK_period,     spawn,		           {.v = (const char*[]){ "mpc", "next", NULL } } },
	//{ MODKEY|ShiftMask,		          XK_period,     spawn,	             {.v = (const char*[]){ "mpc", "repeat", NULL } } },
	//{ MODKEY,			                  XK_m,		       spawn,		           {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	//{ MODKEY|ShiftMask,		          XK_m,		       spawn,		           SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,                       XK_w,          spawn,              {.v = browsercmd} },
	//{ MODKEY,                       XK_e,          spawn,              {.v = (const char*[]){ TERMINAL, "-e", "yazi", NULL } } },
	{ MODKEY,                       XK_b,          togglebar,          {0} },
	{ MODKEY,                       XK_j,          focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_o,          incnmaster,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,          incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,           {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,           {.f = +0.05} },
  { MODKEY,                       XK_Return,     spawn,              {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,     zoom,               {0} },
	{ MODKEY,                       XK_Tab,        view,               {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,         {0} },
	{ MODKEY,                       XK_t,          setlayout,          {.v = &layouts[1]} },
  { MODKEY|ShiftMask,             XK_t,          setlayout,          {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,          {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,          setlayout,          {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,      setlayout,          {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,     {0} },
	{ MODKEY,                       XK_0,          view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,           {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,             {.i = +1 } },
  { MODKEY,                       XK_F5,         xrdb,               {.v = NULL } },
  TAGKEYS(                        XK_1,                              0)
	TAGKEYS(                        XK_2,                              1)
	TAGKEYS(                        XK_3,                              2)
	TAGKEYS(                        XK_4,                              3)
	TAGKEYS(                        XK_5,                              4)
	TAGKEYS(                        XK_6,                              5)
	TAGKEYS(                        XK_7,                              6)
	TAGKEYS(                        XK_8,                              7)
	TAGKEYS(                        XK_9,                              8)
	{ MODKEY|ShiftMask,             XK_q,          quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};

import { call } from 'ffi';
import { define } from 'ffi';
import { dlopen } from 'ffi';
import { dlsym } from 'ffi';
import { pointerSize } from 'ffi';
import { RTLD_NOW } from 'ffi';
import { toArrayBuffer } from 'ffi';

export const GL_VERSION_1_1 = 1;
export const GL_VERSION_1_2 = 1;
export const GL_VERSION_1_3 = 1;
export const GL_ARB_imaging = 1;
export const GL_FALSE = 0;
export const GL_TRUE = 1;
export const GL_BYTE = 0x1400;
export const GL_UNSIGNED_BYTE = 0x1401;
export const GL_SHORT = 0x1402;
export const GL_UNSIGNED_SHORT = 0x1403;
export const GL_INT = 0x1404;
export const GL_UNSIGNED_INT = 0x1405;
export const GL_FLOAT = 0x1406;
export const GL_2_BYTES = 0x1407;
export const GL_3_BYTES = 0x1408;
export const GL_4_BYTES = 0x1409;
export const GL_DOUBLE = 0x140a;
export const GL_POINTS = 0x0000;
export const GL_LINES = 0x0001;
export const GL_LINE_LOOP = 0x0002;
export const GL_LINE_STRIP = 0x0003;
export const GL_TRIANGLES = 0x0004;
export const GL_TRIANGLE_STRIP = 0x0005;
export const GL_TRIANGLE_FAN = 0x0006;
export const GL_QUADS = 0x0007;
export const GL_QUAD_STRIP = 0x0008;
export const GL_POLYGON = 0x0009;
export const GL_VERTEX_ARRAY = 0x8074;
export const GL_NORMAL_ARRAY = 0x8075;
export const GL_COLOR_ARRAY = 0x8076;
export const GL_INDEX_ARRAY = 0x8077;
export const GL_TEXTURE_COORD_ARRAY = 0x8078;
export const GL_EDGE_FLAG_ARRAY = 0x8079;
export const GL_VERTEX_ARRAY_SIZE = 0x807a;
export const GL_VERTEX_ARRAY_TYPE = 0x807b;
export const GL_VERTEX_ARRAY_STRIDE = 0x807c;
export const GL_NORMAL_ARRAY_TYPE = 0x807e;
export const GL_NORMAL_ARRAY_STRIDE = 0x807f;
export const GL_COLOR_ARRAY_SIZE = 0x8081;
export const GL_COLOR_ARRAY_TYPE = 0x8082;
export const GL_COLOR_ARRAY_STRIDE = 0x8083;
export const GL_INDEX_ARRAY_TYPE = 0x8085;
export const GL_INDEX_ARRAY_STRIDE = 0x8086;
export const GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088;
export const GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089;
export const GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808a;
export const GL_EDGE_FLAG_ARRAY_STRIDE = 0x808c;
export const GL_VERTEX_ARRAY_POINTER = 0x808e;
export const GL_NORMAL_ARRAY_POINTER = 0x808f;
export const GL_COLOR_ARRAY_POINTER = 0x8090;
export const GL_INDEX_ARRAY_POINTER = 0x8091;
export const GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092;
export const GL_EDGE_FLAG_ARRAY_POINTER = 0x8093;
export const GL_V2F = 0x2a20;
export const GL_V3F = 0x2a21;
export const GL_C4UB_V2F = 0x2a22;
export const GL_C4UB_V3F = 0x2a23;
export const GL_C3F_V3F = 0x2a24;
export const GL_N3F_V3F = 0x2a25;
export const GL_C4F_N3F_V3F = 0x2a26;
export const GL_T2F_V3F = 0x2a27;
export const GL_T4F_V4F = 0x2a28;
export const GL_T2F_C4UB_V3F = 0x2a29;
export const GL_T2F_C3F_V3F = 0x2a2a;
export const GL_T2F_N3F_V3F = 0x2a2b;
export const GL_T2F_C4F_N3F_V3F = 0x2a2c;
export const GL_T4F_C4F_N3F_V4F = 0x2a2d;
export const GL_MATRIX_MODE = 0x0ba0;
export const GL_MODELVIEW = 0x1700;
export const GL_PROJECTION = 0x1701;
export const GL_TEXTURE = 0x1702;
export const GL_POINT_SMOOTH = 0x0b10;
export const GL_POINT_SIZE = 0x0b11;
export const GL_POINT_SIZE_GRANULARITY = 0x0b13;
export const GL_POINT_SIZE_RANGE = 0x0b12;
export const GL_LINE_SMOOTH = 0x0b20;
export const GL_LINE_STIPPLE = 0x0b24;
export const GL_LINE_STIPPLE_PATTERN = 0x0b25;
export const GL_LINE_STIPPLE_REPEAT = 0x0b26;
export const GL_LINE_WIDTH = 0x0b21;
export const GL_LINE_WIDTH_GRANULARITY = 0x0b23;
export const GL_LINE_WIDTH_RANGE = 0x0b22;
export const GL_POINT = 0x1b00;
export const GL_LINE = 0x1b01;
export const GL_FILL = 0x1b02;
export const GL_CW = 0x0900;
export const GL_CCW = 0x0901;
export const GL_FRONT = 0x0404;
export const GL_BACK = 0x0405;
export const GL_POLYGON_MODE = 0x0b40;
export const GL_POLYGON_SMOOTH = 0x0b41;
export const GL_POLYGON_STIPPLE = 0x0b42;
export const GL_EDGE_FLAG = 0x0b43;
export const GL_CULL_FACE = 0x0b44;
export const GL_CULL_FACE_MODE = 0x0b45;
export const GL_FRONT_FACE = 0x0b46;
export const GL_POLYGON_OFFSET_FACTOR = 0x8038;
export const GL_POLYGON_OFFSET_UNITS = 0x2a00;
export const GL_POLYGON_OFFSET_POINT = 0x2a01;
export const GL_POLYGON_OFFSET_LINE = 0x2a02;
export const GL_POLYGON_OFFSET_FILL = 0x8037;
export const GL_COMPILE = 0x1300;
export const GL_COMPILE_AND_EXECUTE = 0x1301;
export const GL_LIST_BASE = 0x0b32;
export const GL_LIST_INDEX = 0x0b33;
export const GL_LIST_MODE = 0x0b30;
export const GL_NEVER = 0x0200;
export const GL_LESS = 0x0201;
export const GL_EQUAL = 0x0202;
export const GL_LEQUAL = 0x0203;
export const GL_GREATER = 0x0204;
export const GL_NOTEQUAL = 0x0205;
export const GL_GEQUAL = 0x0206;
export const GL_ALWAYS = 0x0207;
export const GL_DEPTH_TEST = 0x0b71;
export const GL_DEPTH_BITS = 0x0d56;
export const GL_DEPTH_CLEAR_VALUE = 0x0b73;
export const GL_DEPTH_FUNC = 0x0b74;
export const GL_DEPTH_RANGE = 0x0b70;
export const GL_DEPTH_WRITEMASK = 0x0b72;
export const GL_DEPTH_COMPONENT = 0x1902;
export const GL_LIGHTING = 0x0b50;
export const GL_LIGHT0 = 0x4000;
export const GL_LIGHT1 = 0x4001;
export const GL_LIGHT2 = 0x4002;
export const GL_LIGHT3 = 0x4003;
export const GL_LIGHT4 = 0x4004;
export const GL_LIGHT5 = 0x4005;
export const GL_LIGHT6 = 0x4006;
export const GL_LIGHT7 = 0x4007;
export const GL_SPOT_EXPONENT = 0x1205;
export const GL_SPOT_CUTOFF = 0x1206;
export const GL_CONSTANT_ATTENUATION = 0x1207;
export const GL_LINEAR_ATTENUATION = 0x1208;
export const GL_QUADRATIC_ATTENUATION = 0x1209;
export const GL_AMBIENT = 0x1200;
export const GL_DIFFUSE = 0x1201;
export const GL_SPECULAR = 0x1202;
export const GL_SHININESS = 0x1601;
export const GL_EMISSION = 0x1600;
export const GL_POSITION = 0x1203;
export const GL_SPOT_DIRECTION = 0x1204;
export const GL_AMBIENT_AND_DIFFUSE = 0x1602;
export const GL_COLOR_INDEXES = 0x1603;
export const GL_LIGHT_MODEL_TWO_SIDE = 0x0b52;
export const GL_LIGHT_MODEL_LOCAL_VIEWER = 0x0b51;
export const GL_LIGHT_MODEL_AMBIENT = 0x0b53;
export const GL_FRONT_AND_BACK = 0x0408;
export const GL_SHADE_MODEL = 0x0b54;
export const GL_FLAT = 0x1d00;
export const GL_SMOOTH = 0x1d01;
export const GL_COLOR_MATERIAL = 0x0b57;
export const GL_COLOR_MATERIAL_FACE = 0x0b55;
export const GL_COLOR_MATERIAL_PARAMETER = 0x0b56;
export const GL_NORMALIZE = 0x0ba1;
export const GL_CLIP_PLANE0 = 0x3000;
export const GL_CLIP_PLANE1 = 0x3001;
export const GL_CLIP_PLANE2 = 0x3002;
export const GL_CLIP_PLANE3 = 0x3003;
export const GL_CLIP_PLANE4 = 0x3004;
export const GL_CLIP_PLANE5 = 0x3005;
export const GL_ACCUM_RED_BITS = 0x0d58;
export const GL_ACCUM_GREEN_BITS = 0x0d59;
export const GL_ACCUM_BLUE_BITS = 0x0d5a;
export const GL_ACCUM_ALPHA_BITS = 0x0d5b;
export const GL_ACCUM_CLEAR_VALUE = 0x0b80;
export const GL_ACCUM = 0x0100;
export const GL_ADD = 0x0104;
export const GL_LOAD = 0x0101;
export const GL_MULT = 0x0103;
export const GL_RETURN = 0x0102;
export const GL_ALPHA_TEST = 0x0bc0;
export const GL_ALPHA_TEST_REF = 0x0bc2;
export const GL_ALPHA_TEST_FUNC = 0x0bc1;
export const GL_BLEND = 0x0be2;
export const GL_BLEND_SRC = 0x0be1;
export const GL_BLEND_DST = 0x0be0;
export const GL_ZERO = 0;
export const GL_ONE = 1;
export const GL_SRC_COLOR = 0x0300;
export const GL_ONE_MINUS_SRC_COLOR = 0x0301;
export const GL_SRC_ALPHA = 0x0302;
export const GL_ONE_MINUS_SRC_ALPHA = 0x0303;
export const GL_DST_ALPHA = 0x0304;
export const GL_ONE_MINUS_DST_ALPHA = 0x0305;
export const GL_DST_COLOR = 0x0306;
export const GL_ONE_MINUS_DST_COLOR = 0x0307;
export const GL_SRC_ALPHA_SATURATE = 0x0308;
export const GL_FEEDBACK = 0x1c01;
export const GL_RENDER = 0x1c00;
export const GL_SELECT = 0x1c02;
export const GL_2D = 0x0600;
export const GL_3D = 0x0601;
export const GL_3D_COLOR = 0x0602;
export const GL_3D_COLOR_TEXTURE = 0x0603;
export const GL_4D_COLOR_TEXTURE = 0x0604;
export const GL_POINT_TOKEN = 0x0701;
export const GL_LINE_TOKEN = 0x0702;
export const GL_LINE_RESET_TOKEN = 0x0707;
export const GL_POLYGON_TOKEN = 0x0703;
export const GL_BITMAP_TOKEN = 0x0704;
export const GL_DRAW_PIXEL_TOKEN = 0x0705;
export const GL_COPY_PIXEL_TOKEN = 0x0706;
export const GL_PASS_THROUGH_TOKEN = 0x0700;
export const GL_FEEDBACK_BUFFER_POINTER = 0x0df0;
export const GL_FEEDBACK_BUFFER_SIZE = 0x0df1;
export const GL_FEEDBACK_BUFFER_TYPE = 0x0df2;
export const GL_SELECTION_BUFFER_POINTER = 0x0df3;
export const GL_SELECTION_BUFFER_SIZE = 0x0df4;
export const GL_FOG = 0x0b60;
export const GL_FOG_MODE = 0x0b65;
export const GL_FOG_DENSITY = 0x0b62;
export const GL_FOG_COLOR = 0x0b66;
export const GL_FOG_INDEX = 0x0b61;
export const GL_FOG_START = 0x0b63;
export const GL_FOG_END = 0x0b64;
export const GL_LINEAR = 0x2601;
export const GL_EXP = 0x0800;
export const GL_EXP2 = 0x0801;
export const GL_LOGIC_OP = 0x0bf1;
export const GL_INDEX_LOGIC_OP = 0x0bf1;
export const GL_COLOR_LOGIC_OP = 0x0bf2;
export const GL_LOGIC_OP_MODE = 0x0bf0;
export const GL_CLEAR = 0x1500;
export const GL_SET = 0x150f;
export const GL_COPY = 0x1503;
export const GL_COPY_INVERTED = 0x150c;
export const GL_NOOP = 0x1505;
export const GL_INVERT = 0x150a;
export const GL_AND = 0x1501;
export const GL_NAND = 0x150e;
export const GL_OR = 0x1507;
export const GL_NOR = 0x1508;
export const GL_XOR = 0x1506;
export const GL_EQUIV = 0x1509;
export const GL_AND_REVERSE = 0x1502;
export const GL_AND_INVERTED = 0x1504;
export const GL_OR_REVERSE = 0x150b;
export const GL_OR_INVERTED = 0x150d;
export const GL_STENCIL_BITS = 0x0d57;
export const GL_STENCIL_TEST = 0x0b90;
export const GL_STENCIL_CLEAR_VALUE = 0x0b91;
export const GL_STENCIL_FUNC = 0x0b92;
export const GL_STENCIL_VALUE_MASK = 0x0b93;
export const GL_STENCIL_FAIL = 0x0b94;
export const GL_STENCIL_PASS_DEPTH_FAIL = 0x0b95;
export const GL_STENCIL_PASS_DEPTH_PASS = 0x0b96;
export const GL_STENCIL_REF = 0x0b97;
export const GL_STENCIL_WRITEMASK = 0x0b98;
export const GL_STENCIL_INDEX = 0x1901;
export const GL_KEEP = 0x1e00;
export const GL_REPLACE = 0x1e01;
export const GL_INCR = 0x1e02;
export const GL_DECR = 0x1e03;
export const GL_NONE = 0;
export const GL_LEFT = 0x0406;
export const GL_RIGHT = 0x0407;
export const GL_FRONT_LEFT = 0x0400;
export const GL_FRONT_RIGHT = 0x0401;
export const GL_BACK_LEFT = 0x0402;
export const GL_BACK_RIGHT = 0x0403;
export const GL_AUX0 = 0x0409;
export const GL_AUX1 = 0x040a;
export const GL_AUX2 = 0x040b;
export const GL_AUX3 = 0x040c;
export const GL_COLOR_INDEX = 0x1900;
export const GL_RED = 0x1903;
export const GL_GREEN = 0x1904;
export const GL_BLUE = 0x1905;
export const GL_ALPHA = 0x1906;
export const GL_LUMINANCE = 0x1909;
export const GL_LUMINANCE_ALPHA = 0x190a;
export const GL_ALPHA_BITS = 0x0d55;
export const GL_RED_BITS = 0x0d52;
export const GL_GREEN_BITS = 0x0d53;
export const GL_BLUE_BITS = 0x0d54;
export const GL_INDEX_BITS = 0x0d51;
export const GL_SUBPIXEL_BITS = 0x0d50;
export const GL_AUX_BUFFERS = 0x0c00;
export const GL_READ_BUFFER = 0x0c02;
export const GL_DRAW_BUFFER = 0x0c01;
export const GL_DOUBLEBUFFER = 0x0c32;
export const GL_STEREO = 0x0c33;
export const GL_BITMAP = 0x1a00;
export const GL_COLOR = 0x1800;
export const GL_DEPTH = 0x1801;
export const GL_STENCIL = 0x1802;
export const GL_DITHER = 0x0bd0;
export const GL_RGB = 0x1907;
export const GL_RGBA = 0x1908;
export const GL_MAX_LIST_NESTING = 0x0b31;
export const GL_MAX_EVAL_ORDER = 0x0d30;
export const GL_MAX_LIGHTS = 0x0d31;
export const GL_MAX_CLIP_PLANES = 0x0d32;
export const GL_MAX_TEXTURE_SIZE = 0x0d33;
export const GL_MAX_PIXEL_MAP_TABLE = 0x0d34;
export const GL_MAX_ATTRIB_STACK_DEPTH = 0x0d35;
export const GL_MAX_MODELVIEW_STACK_DEPTH = 0x0d36;
export const GL_MAX_NAME_STACK_DEPTH = 0x0d37;
export const GL_MAX_PROJECTION_STACK_DEPTH = 0x0d38;
export const GL_MAX_TEXTURE_STACK_DEPTH = 0x0d39;
export const GL_MAX_VIEWPORT_DIMS = 0x0d3a;
export const GL_MAX_CLIENT_ATTRIB_STACK_DEPTH = 0x0d3b;
export const GL_ATTRIB_STACK_DEPTH = 0x0bb0;
export const GL_CLIENT_ATTRIB_STACK_DEPTH = 0x0bb1;
export const GL_COLOR_CLEAR_VALUE = 0x0c22;
export const GL_COLOR_WRITEMASK = 0x0c23;
export const GL_CURRENT_INDEX = 0x0b01;
export const GL_CURRENT_COLOR = 0x0b00;
export const GL_CURRENT_NORMAL = 0x0b02;
export const GL_CURRENT_RASTER_COLOR = 0x0b04;
export const GL_CURRENT_RASTER_DISTANCE = 0x0b09;
export const GL_CURRENT_RASTER_INDEX = 0x0b05;
export const GL_CURRENT_RASTER_POSITION = 0x0b07;
export const GL_CURRENT_RASTER_TEXTURE_COORDS = 0x0b06;
export const GL_CURRENT_RASTER_POSITION_VALID = 0x0b08;
export const GL_CURRENT_TEXTURE_COORDS = 0x0b03;
export const GL_INDEX_CLEAR_VALUE = 0x0c20;
export const GL_INDEX_MODE = 0x0c30;
export const GL_INDEX_WRITEMASK = 0x0c21;
export const GL_MODELVIEW_MATRIX = 0x0ba6;
export const GL_MODELVIEW_STACK_DEPTH = 0x0ba3;
export const GL_NAME_STACK_DEPTH = 0x0d70;
export const GL_PROJECTION_MATRIX = 0x0ba7;
export const GL_PROJECTION_STACK_DEPTH = 0x0ba4;
export const GL_RENDER_MODE = 0x0c40;
export const GL_RGBA_MODE = 0x0c31;
export const GL_TEXTURE_MATRIX = 0x0ba8;
export const GL_TEXTURE_STACK_DEPTH = 0x0ba5;
export const GL_VIEWPORT = 0x0ba2;
export const GL_AUTO_NORMAL = 0x0d80;
export const GL_MAP1_COLOR_4 = 0x0d90;
export const GL_MAP1_INDEX = 0x0d91;
export const GL_MAP1_NORMAL = 0x0d92;
export const GL_MAP1_TEXTURE_COORD_1 = 0x0d93;
export const GL_MAP1_TEXTURE_COORD_2 = 0x0d94;
export const GL_MAP1_TEXTURE_COORD_3 = 0x0d95;
export const GL_MAP1_TEXTURE_COORD_4 = 0x0d96;
export const GL_MAP1_VERTEX_3 = 0x0d97;
export const GL_MAP1_VERTEX_4 = 0x0d98;
export const GL_MAP2_COLOR_4 = 0x0db0;
export const GL_MAP2_INDEX = 0x0db1;
export const GL_MAP2_NORMAL = 0x0db2;
export const GL_MAP2_TEXTURE_COORD_1 = 0x0db3;
export const GL_MAP2_TEXTURE_COORD_2 = 0x0db4;
export const GL_MAP2_TEXTURE_COORD_3 = 0x0db5;
export const GL_MAP2_TEXTURE_COORD_4 = 0x0db6;
export const GL_MAP2_VERTEX_3 = 0x0db7;
export const GL_MAP2_VERTEX_4 = 0x0db8;
export const GL_MAP1_GRID_DOMAIN = 0x0dd0;
export const GL_MAP1_GRID_SEGMENTS = 0x0dd1;
export const GL_MAP2_GRID_DOMAIN = 0x0dd2;
export const GL_MAP2_GRID_SEGMENTS = 0x0dd3;
export const GL_COEFF = 0x0a00;
export const GL_ORDER = 0x0a01;
export const GL_DOMAIN = 0x0a02;
export const GL_PERSPECTIVE_CORRECTION_HINT = 0x0c50;
export const GL_POINT_SMOOTH_HINT = 0x0c51;
export const GL_LINE_SMOOTH_HINT = 0x0c52;
export const GL_POLYGON_SMOOTH_HINT = 0x0c53;
export const GL_FOG_HINT = 0x0c54;
export const GL_DONT_CARE = 0x1100;
export const GL_FASTEST = 0x1101;
export const GL_NICEST = 0x1102;
export const GL_SCISSOR_BOX = 0x0c10;
export const GL_SCISSOR_TEST = 0x0c11;
export const GL_MAP_COLOR = 0x0d10;
export const GL_MAP_STENCIL = 0x0d11;
export const GL_INDEX_SHIFT = 0x0d12;
export const GL_INDEX_OFFSET = 0x0d13;
export const GL_RED_SCALE = 0x0d14;
export const GL_RED_BIAS = 0x0d15;
export const GL_GREEN_SCALE = 0x0d18;
export const GL_GREEN_BIAS = 0x0d19;
export const GL_BLUE_SCALE = 0x0d1a;
export const GL_BLUE_BIAS = 0x0d1b;
export const GL_ALPHA_SCALE = 0x0d1c;
export const GL_ALPHA_BIAS = 0x0d1d;
export const GL_DEPTH_SCALE = 0x0d1e;
export const GL_DEPTH_BIAS = 0x0d1f;
export const GL_PIXEL_MAP_S_TO_S_SIZE = 0x0cb1;
export const GL_PIXEL_MAP_I_TO_I_SIZE = 0x0cb0;
export const GL_PIXEL_MAP_I_TO_R_SIZE = 0x0cb2;
export const GL_PIXEL_MAP_I_TO_G_SIZE = 0x0cb3;
export const GL_PIXEL_MAP_I_TO_B_SIZE = 0x0cb4;
export const GL_PIXEL_MAP_I_TO_A_SIZE = 0x0cb5;
export const GL_PIXEL_MAP_R_TO_R_SIZE = 0x0cb6;
export const GL_PIXEL_MAP_G_TO_G_SIZE = 0x0cb7;
export const GL_PIXEL_MAP_B_TO_B_SIZE = 0x0cb8;
export const GL_PIXEL_MAP_A_TO_A_SIZE = 0x0cb9;
export const GL_PIXEL_MAP_S_TO_S = 0x0c71;
export const GL_PIXEL_MAP_I_TO_I = 0x0c70;
export const GL_PIXEL_MAP_I_TO_R = 0x0c72;
export const GL_PIXEL_MAP_I_TO_G = 0x0c73;
export const GL_PIXEL_MAP_I_TO_B = 0x0c74;
export const GL_PIXEL_MAP_I_TO_A = 0x0c75;
export const GL_PIXEL_MAP_R_TO_R = 0x0c76;
export const GL_PIXEL_MAP_G_TO_G = 0x0c77;
export const GL_PIXEL_MAP_B_TO_B = 0x0c78;
export const GL_PIXEL_MAP_A_TO_A = 0x0c79;
export const GL_PACK_ALIGNMENT = 0x0d05;
export const GL_PACK_LSB_FIRST = 0x0d01;
export const GL_PACK_ROW_LENGTH = 0x0d02;
export const GL_PACK_SKIP_PIXELS = 0x0d04;
export const GL_PACK_SKIP_ROWS = 0x0d03;
export const GL_PACK_SWAP_BYTES = 0x0d00;
export const GL_UNPACK_ALIGNMENT = 0x0cf5;
export const GL_UNPACK_LSB_FIRST = 0x0cf1;
export const GL_UNPACK_ROW_LENGTH = 0x0cf2;
export const GL_UNPACK_SKIP_PIXELS = 0x0cf4;
export const GL_UNPACK_SKIP_ROWS = 0x0cf3;
export const GL_UNPACK_SWAP_BYTES = 0x0cf0;
export const GL_ZOOM_X = 0x0d16;
export const GL_ZOOM_Y = 0x0d17;
export const GL_TEXTURE_ENV = 0x2300;
export const GL_TEXTURE_ENV_MODE = 0x2200;
export const GL_TEXTURE_1D = 0x0de0;
export const GL_TEXTURE_2D = 0x0de1;
export const GL_TEXTURE_WRAP_S = 0x2802;
export const GL_TEXTURE_WRAP_T = 0x2803;
export const GL_TEXTURE_MAG_FILTER = 0x2800;
export const GL_TEXTURE_MIN_FILTER = 0x2801;
export const GL_TEXTURE_ENV_COLOR = 0x2201;
export const GL_TEXTURE_GEN_S = 0x0c60;
export const GL_TEXTURE_GEN_T = 0x0c61;
export const GL_TEXTURE_GEN_R = 0x0c62;
export const GL_TEXTURE_GEN_Q = 0x0c63;
export const GL_TEXTURE_GEN_MODE = 0x2500;
export const GL_TEXTURE_BORDER_COLOR = 0x1004;
export const GL_TEXTURE_WIDTH = 0x1000;
export const GL_TEXTURE_HEIGHT = 0x1001;
export const GL_TEXTURE_BORDER = 0x1005;
export const GL_TEXTURE_COMPONENTS = 0x1003;
export const GL_TEXTURE_RED_SIZE = 0x805c;
export const GL_TEXTURE_GREEN_SIZE = 0x805d;
export const GL_TEXTURE_BLUE_SIZE = 0x805e;
export const GL_TEXTURE_ALPHA_SIZE = 0x805f;
export const GL_TEXTURE_LUMINANCE_SIZE = 0x8060;
export const GL_TEXTURE_INTENSITY_SIZE = 0x8061;
export const GL_NEAREST_MIPMAP_NEAREST = 0x2700;
export const GL_NEAREST_MIPMAP_LINEAR = 0x2702;
export const GL_LINEAR_MIPMAP_NEAREST = 0x2701;
export const GL_LINEAR_MIPMAP_LINEAR = 0x2703;
export const GL_OBJECT_LINEAR = 0x2401;
export const GL_OBJECT_PLANE = 0x2501;
export const GL_EYE_LINEAR = 0x2400;
export const GL_EYE_PLANE = 0x2502;
export const GL_SPHERE_MAP = 0x2402;
export const GL_DECAL = 0x2101;
export const GL_MODULATE = 0x2100;
export const GL_NEAREST = 0x2600;
export const GL_REPEAT = 0x2901;
export const GL_CLAMP = 0x2900;
export const GL_S = 0x2000;
export const GL_T = 0x2001;
export const GL_R = 0x2002;
export const GL_Q = 0x2003;
export const GL_VENDOR = 0x1f00;
export const GL_RENDERER = 0x1f01;
export const GL_VERSION = 0x1f02;
export const GL_EXTENSIONS = 0x1f03;
export const GL_NO_ERROR = 0;
export const GL_INVALID_ENUM = 0x0500;
export const GL_INVALID_VALUE = 0x0501;
export const GL_INVALID_OPERATION = 0x0502;
export const GL_STACK_OVERFLOW = 0x0503;
export const GL_STACK_UNDERFLOW = 0x0504;
export const GL_OUT_OF_MEMORY = 0x0505;
export const GL_CURRENT_BIT = 0x00000001;
export const GL_POINT_BIT = 0x00000002;
export const GL_LINE_BIT = 0x00000004;
export const GL_POLYGON_BIT = 0x00000008;
export const GL_POLYGON_STIPPLE_BIT = 0x00000010;
export const GL_PIXEL_MODE_BIT = 0x00000020;
export const GL_LIGHTING_BIT = 0x00000040;
export const GL_FOG_BIT = 0x00000080;
export const GL_DEPTH_BUFFER_BIT = 0x00000100;
export const GL_ACCUM_BUFFER_BIT = 0x00000200;
export const GL_STENCIL_BUFFER_BIT = 0x00000400;
export const GL_VIEWPORT_BIT = 0x00000800;
export const GL_TRANSFORM_BIT = 0x00001000;
export const GL_ENABLE_BIT = 0x00002000;
export const GL_COLOR_BUFFER_BIT = 0x00004000;
export const GL_HINT_BIT = 0x00008000;
export const GL_EVAL_BIT = 0x00010000;
export const GL_LIST_BIT = 0x00020000;
export const GL_TEXTURE_BIT = 0x00040000;
export const GL_SCISSOR_BIT = 0x00080000;
export const GL_ALL_ATTRIB_BITS = 0xffffffff;
export const GL_PROXY_TEXTURE_1D = 0x8063;
export const GL_PROXY_TEXTURE_2D = 0x8064;
export const GL_TEXTURE_PRIORITY = 0x8066;
export const GL_TEXTURE_RESIDENT = 0x8067;
export const GL_TEXTURE_BINDING_1D = 0x8068;
export const GL_TEXTURE_BINDING_2D = 0x8069;
export const GL_TEXTURE_INTERNAL_FORMAT = 0x1003;
export const GL_ALPHA4 = 0x803b;
export const GL_ALPHA8 = 0x803c;
export const GL_ALPHA12 = 0x803d;
export const GL_ALPHA16 = 0x803e;
export const GL_LUMINANCE4 = 0x803f;
export const GL_LUMINANCE8 = 0x8040;
export const GL_LUMINANCE12 = 0x8041;
export const GL_LUMINANCE16 = 0x8042;
export const GL_LUMINANCE4_ALPHA4 = 0x8043;
export const GL_LUMINANCE6_ALPHA2 = 0x8044;
export const GL_LUMINANCE8_ALPHA8 = 0x8045;
export const GL_LUMINANCE12_ALPHA4 = 0x8046;
export const GL_LUMINANCE12_ALPHA12 = 0x8047;
export const GL_LUMINANCE16_ALPHA16 = 0x8048;
export const GL_INTENSITY = 0x8049;
export const GL_INTENSITY4 = 0x804a;
export const GL_INTENSITY8 = 0x804b;
export const GL_INTENSITY12 = 0x804c;
export const GL_INTENSITY16 = 0x804d;
export const GL_R3_G3_B2 = 0x2a10;
export const GL_RGB4 = 0x804f;
export const GL_RGB5 = 0x8050;
export const GL_RGB8 = 0x8051;
export const GL_RGB10 = 0x8052;
export const GL_RGB12 = 0x8053;
export const GL_RGB16 = 0x8054;
export const GL_RGBA2 = 0x8055;
export const GL_RGBA4 = 0x8056;
export const GL_RGB5_A1 = 0x8057;
export const GL_RGBA8 = 0x8058;
export const GL_RGB10_A2 = 0x8059;
export const GL_RGBA12 = 0x805a;
export const GL_RGBA16 = 0x805b;
export const GL_CLIENT_PIXEL_STORE_BIT = 0x00000001;
export const GL_CLIENT_VERTEX_ARRAY_BIT = 0x00000002;
export const GL_ALL_CLIENT_ATTRIB_BITS = 0xffffffff;
export const GL_CLIENT_ALL_ATTRIB_BITS = 0xffffffff;
export const GL_RESCALE_NORMAL = 0x803a;
export const GL_CLAMP_TO_EDGE = 0x812f;
export const GL_MAX_ELEMENTS_VERTICES = 0x80e8;
export const GL_MAX_ELEMENTS_INDICES = 0x80e9;
export const GL_BGR = 0x80e0;
export const GL_BGRA = 0x80e1;
export const GL_UNSIGNED_BYTE_3_3_2 = 0x8032;
export const GL_UNSIGNED_BYTE_2_3_3_REV = 0x8362;
export const GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
export const GL_UNSIGNED_SHORT_5_6_5_REV = 0x8364;
export const GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
export const GL_UNSIGNED_SHORT_4_4_4_4_REV = 0x8365;
export const GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
export const GL_UNSIGNED_SHORT_1_5_5_5_REV = 0x8366;
export const GL_UNSIGNED_INT_8_8_8_8 = 0x8035;
export const GL_UNSIGNED_INT_8_8_8_8_REV = 0x8367;
export const GL_UNSIGNED_INT_10_10_10_2 = 0x8036;
export const GL_UNSIGNED_INT_2_10_10_10_REV = 0x8368;
export const GL_LIGHT_MODEL_COLOR_CONTROL = 0x81f8;
export const GL_SINGLE_COLOR = 0x81f9;
export const GL_SEPARATE_SPECULAR_COLOR = 0x81fa;
export const GL_TEXTURE_MIN_LOD = 0x813a;
export const GL_TEXTURE_MAX_LOD = 0x813b;
export const GL_TEXTURE_BASE_LEVEL = 0x813c;
export const GL_TEXTURE_MAX_LEVEL = 0x813d;
export const GL_SMOOTH_POINT_SIZE_RANGE = 0x0b12;
export const GL_SMOOTH_POINT_SIZE_GRANULARITY = 0x0b13;
export const GL_SMOOTH_LINE_WIDTH_RANGE = 0x0b22;
export const GL_SMOOTH_LINE_WIDTH_GRANULARITY = 0x0b23;
export const GL_ALIASED_POINT_SIZE_RANGE = 0x846d;
export const GL_ALIASED_LINE_WIDTH_RANGE = 0x846e;
export const GL_PACK_SKIP_IMAGES = 0x806b;
export const GL_PACK_IMAGE_HEIGHT = 0x806c;
export const GL_UNPACK_SKIP_IMAGES = 0x806d;
export const GL_UNPACK_IMAGE_HEIGHT = 0x806e;
export const GL_TEXTURE_3D = 0x806f;
export const GL_PROXY_TEXTURE_3D = 0x8070;
export const GL_TEXTURE_DEPTH = 0x8071;
export const GL_TEXTURE_WRAP_R = 0x8072;
export const GL_MAX_3D_TEXTURE_SIZE = 0x8073;
export const GL_TEXTURE_BINDING_3D = 0x806a;
export const GL_CONSTANT_COLOR = 0x8001;
export const GL_ONE_MINUS_CONSTANT_COLOR = 0x8002;
export const GL_CONSTANT_ALPHA = 0x8003;
export const GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004;
export const GL_COLOR_TABLE = 0x80d0;
export const GL_POST_CONVOLUTION_COLOR_TABLE = 0x80d1;
export const GL_POST_COLOR_MATRIX_COLOR_TABLE = 0x80d2;
export const GL_PROXY_COLOR_TABLE = 0x80d3;
export const GL_PROXY_POST_CONVOLUTION_COLOR_TABLE = 0x80d4;
export const GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE = 0x80d5;
export const GL_COLOR_TABLE_SCALE = 0x80d6;
export const GL_COLOR_TABLE_BIAS = 0x80d7;
export const GL_COLOR_TABLE_FORMAT = 0x80d8;
export const GL_COLOR_TABLE_WIDTH = 0x80d9;
export const GL_COLOR_TABLE_RED_SIZE = 0x80da;
export const GL_COLOR_TABLE_GREEN_SIZE = 0x80db;
export const GL_COLOR_TABLE_BLUE_SIZE = 0x80dc;
export const GL_COLOR_TABLE_ALPHA_SIZE = 0x80dd;
export const GL_COLOR_TABLE_LUMINANCE_SIZE = 0x80de;
export const GL_COLOR_TABLE_INTENSITY_SIZE = 0x80df;
export const GL_CONVOLUTION_1D = 0x8010;
export const GL_CONVOLUTION_2D = 0x8011;
export const GL_SEPARABLE_2D = 0x8012;
export const GL_CONVOLUTION_BORDER_MODE = 0x8013;
export const GL_CONVOLUTION_FILTER_SCALE = 0x8014;
export const GL_CONVOLUTION_FILTER_BIAS = 0x8015;
export const GL_REDUCE = 0x8016;
export const GL_CONVOLUTION_FORMAT = 0x8017;
export const GL_CONVOLUTION_WIDTH = 0x8018;
export const GL_CONVOLUTION_HEIGHT = 0x8019;
export const GL_MAX_CONVOLUTION_WIDTH = 0x801a;
export const GL_MAX_CONVOLUTION_HEIGHT = 0x801b;
export const GL_POST_CONVOLUTION_RED_SCALE = 0x801c;
export const GL_POST_CONVOLUTION_GREEN_SCALE = 0x801d;
export const GL_POST_CONVOLUTION_BLUE_SCALE = 0x801e;
export const GL_POST_CONVOLUTION_ALPHA_SCALE = 0x801f;
export const GL_POST_CONVOLUTION_RED_BIAS = 0x8020;
export const GL_POST_CONVOLUTION_GREEN_BIAS = 0x8021;
export const GL_POST_CONVOLUTION_BLUE_BIAS = 0x8022;
export const GL_POST_CONVOLUTION_ALPHA_BIAS = 0x8023;
export const GL_CONSTANT_BORDER = 0x8151;
export const GL_REPLICATE_BORDER = 0x8153;
export const GL_CONVOLUTION_BORDER_COLOR = 0x8154;
export const GL_COLOR_MATRIX = 0x80b1;
export const GL_COLOR_MATRIX_STACK_DEPTH = 0x80b2;
export const GL_MAX_COLOR_MATRIX_STACK_DEPTH = 0x80b3;
export const GL_POST_COLOR_MATRIX_RED_SCALE = 0x80b4;
export const GL_POST_COLOR_MATRIX_GREEN_SCALE = 0x80b5;
export const GL_POST_COLOR_MATRIX_BLUE_SCALE = 0x80b6;
export const GL_POST_COLOR_MATRIX_ALPHA_SCALE = 0x80b7;
export const GL_POST_COLOR_MATRIX_RED_BIAS = 0x80b8;
export const GL_POST_COLOR_MATRIX_GREEN_BIAS = 0x80b9;
export const GL_POST_COLOR_MATRIX_BLUE_BIAS = 0x80ba;
export const GL_POST_COLOR_MATRIX_ALPHA_BIAS = 0x80bb;
export const GL_HISTOGRAM = 0x8024;
export const GL_PROXY_HISTOGRAM = 0x8025;
export const GL_HISTOGRAM_WIDTH = 0x8026;
export const GL_HISTOGRAM_FORMAT = 0x8027;
export const GL_HISTOGRAM_RED_SIZE = 0x8028;
export const GL_HISTOGRAM_GREEN_SIZE = 0x8029;
export const GL_HISTOGRAM_BLUE_SIZE = 0x802a;
export const GL_HISTOGRAM_ALPHA_SIZE = 0x802b;
export const GL_HISTOGRAM_LUMINANCE_SIZE = 0x802c;
export const GL_HISTOGRAM_SINK = 0x802d;
export const GL_MINMAX = 0x802e;
export const GL_MINMAX_FORMAT = 0x802f;
export const GL_MINMAX_SINK = 0x8030;
export const GL_TABLE_TOO_LARGE = 0x8031;
export const GL_BLEND_EQUATION = 0x8009;
export const GL_MIN = 0x8007;
export const GL_MAX = 0x8008;
export const GL_FUNC_ADD = 0x8006;
export const GL_FUNC_SUBTRACT = 0x800a;
export const GL_FUNC_REVERSE_SUBTRACT = 0x800b;
export const GL_BLEND_COLOR = 0x8005;
export const GL_TEXTURE0 = 0x84c0;
export const GL_TEXTURE1 = 0x84c1;
export const GL_TEXTURE2 = 0x84c2;
export const GL_TEXTURE3 = 0x84c3;
export const GL_TEXTURE4 = 0x84c4;
export const GL_TEXTURE5 = 0x84c5;
export const GL_TEXTURE6 = 0x84c6;
export const GL_TEXTURE7 = 0x84c7;
export const GL_TEXTURE8 = 0x84c8;
export const GL_TEXTURE9 = 0x84c9;
export const GL_TEXTURE10 = 0x84ca;
export const GL_TEXTURE11 = 0x84cb;
export const GL_TEXTURE12 = 0x84cc;
export const GL_TEXTURE13 = 0x84cd;
export const GL_TEXTURE14 = 0x84ce;
export const GL_TEXTURE15 = 0x84cf;
export const GL_TEXTURE16 = 0x84d0;
export const GL_TEXTURE17 = 0x84d1;
export const GL_TEXTURE18 = 0x84d2;
export const GL_TEXTURE19 = 0x84d3;
export const GL_TEXTURE20 = 0x84d4;
export const GL_TEXTURE21 = 0x84d5;
export const GL_TEXTURE22 = 0x84d6;
export const GL_TEXTURE23 = 0x84d7;
export const GL_TEXTURE24 = 0x84d8;
export const GL_TEXTURE25 = 0x84d9;
export const GL_TEXTURE26 = 0x84da;
export const GL_TEXTURE27 = 0x84db;
export const GL_TEXTURE28 = 0x84dc;
export const GL_TEXTURE29 = 0x84dd;
export const GL_TEXTURE30 = 0x84de;
export const GL_TEXTURE31 = 0x84df;
export const GL_ACTIVE_TEXTURE = 0x84e0;
export const GL_CLIENT_ACTIVE_TEXTURE = 0x84e1;
export const GL_MAX_TEXTURE_UNITS = 0x84e2;
export const GL_NORMAL_MAP = 0x8511;
export const GL_REFLECTION_MAP = 0x8512;
export const GL_TEXTURE_CUBE_MAP = 0x8513;
export const GL_TEXTURE_BINDING_CUBE_MAP = 0x8514;
export const GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
export const GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
export const GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
export const GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
export const GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
export const GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851a;
export const GL_PROXY_TEXTURE_CUBE_MAP = 0x851b;
export const GL_MAX_CUBE_MAP_TEXTURE_SIZE = 0x851c;
export const GL_COMPRESSED_ALPHA = 0x84e9;
export const GL_COMPRESSED_LUMINANCE = 0x84ea;
export const GL_COMPRESSED_LUMINANCE_ALPHA = 0x84eb;
export const GL_COMPRESSED_INTENSITY = 0x84ec;
export const GL_COMPRESSED_RGB = 0x84ed;
export const GL_COMPRESSED_RGBA = 0x84ee;
export const GL_TEXTURE_COMPRESSION_HINT = 0x84ef;
export const GL_TEXTURE_COMPRESSED_IMAGE_SIZE = 0x86a0;
export const GL_TEXTURE_COMPRESSED = 0x86a1;
export const GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86a2;
export const GL_COMPRESSED_TEXTURE_FORMATS = 0x86a3;
export const GL_MULTISAMPLE = 0x809d;
export const GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809e;
export const GL_SAMPLE_ALPHA_TO_ONE = 0x809f;
export const GL_SAMPLE_COVERAGE = 0x80a0;
export const GL_SAMPLE_BUFFERS = 0x80a8;
export const GL_SAMPLES = 0x80a9;
export const GL_SAMPLE_COVERAGE_VALUE = 0x80aa;
export const GL_SAMPLE_COVERAGE_INVERT = 0x80ab;
export const GL_MULTISAMPLE_BIT = 0x20000000;
export const GL_TRANSPOSE_MODELVIEW_MATRIX = 0x84e3;
export const GL_TRANSPOSE_PROJECTION_MATRIX = 0x84e4;
export const GL_TRANSPOSE_TEXTURE_MATRIX = 0x84e5;
export const GL_TRANSPOSE_COLOR_MATRIX = 0x84e6;
export const GL_COMBINE = 0x8570;
export const GL_COMBINE_RGB = 0x8571;
export const GL_COMBINE_ALPHA = 0x8572;
export const GL_SOURCE0_RGB = 0x8580;
export const GL_SOURCE1_RGB = 0x8581;
export const GL_SOURCE2_RGB = 0x8582;
export const GL_SOURCE0_ALPHA = 0x8588;
export const GL_SOURCE1_ALPHA = 0x8589;
export const GL_SOURCE2_ALPHA = 0x858a;
export const GL_OPERAND0_RGB = 0x8590;
export const GL_OPERAND1_RGB = 0x8591;
export const GL_OPERAND2_RGB = 0x8592;
export const GL_OPERAND0_ALPHA = 0x8598;
export const GL_OPERAND1_ALPHA = 0x8599;
export const GL_OPERAND2_ALPHA = 0x859a;
export const GL_RGB_SCALE = 0x8573;
export const GL_ADD_SIGNED = 0x8574;
export const GL_INTERPOLATE = 0x8575;
export const GL_SUBTRACT = 0x84e7;
export const GL_CONSTANT = 0x8576;
export const GL_PRIMARY_COLOR = 0x8577;
export const GL_PREVIOUS = 0x8578;
export const GL_DOT3_RGB = 0x86ae;
export const GL_DOT3_RGBA = 0x86af;
export const GL_CLAMP_TO_BORDER = 0x812d;
export const GL_ARB_multitexture = 1;
export const GL_TEXTURE0_ARB = 0x84c0;
export const GL_TEXTURE1_ARB = 0x84c1;
export const GL_TEXTURE2_ARB = 0x84c2;
export const GL_TEXTURE3_ARB = 0x84c3;
export const GL_TEXTURE4_ARB = 0x84c4;
export const GL_TEXTURE5_ARB = 0x84c5;
export const GL_TEXTURE6_ARB = 0x84c6;
export const GL_TEXTURE7_ARB = 0x84c7;
export const GL_TEXTURE8_ARB = 0x84c8;
export const GL_TEXTURE9_ARB = 0x84c9;
export const GL_TEXTURE10_ARB = 0x84ca;
export const GL_TEXTURE11_ARB = 0x84cb;
export const GL_TEXTURE12_ARB = 0x84cc;
export const GL_TEXTURE13_ARB = 0x84cd;
export const GL_TEXTURE14_ARB = 0x84ce;
export const GL_TEXTURE15_ARB = 0x84cf;
export const GL_TEXTURE16_ARB = 0x84d0;
export const GL_TEXTURE17_ARB = 0x84d1;
export const GL_TEXTURE18_ARB = 0x84d2;
export const GL_TEXTURE19_ARB = 0x84d3;
export const GL_TEXTURE20_ARB = 0x84d4;
export const GL_TEXTURE21_ARB = 0x84d5;
export const GL_TEXTURE22_ARB = 0x84d6;
export const GL_TEXTURE23_ARB = 0x84d7;
export const GL_TEXTURE24_ARB = 0x84d8;
export const GL_TEXTURE25_ARB = 0x84d9;
export const GL_TEXTURE26_ARB = 0x84da;
export const GL_TEXTURE27_ARB = 0x84db;
export const GL_TEXTURE28_ARB = 0x84dc;
export const GL_TEXTURE29_ARB = 0x84dd;
export const GL_TEXTURE30_ARB = 0x84de;
export const GL_TEXTURE31_ARB = 0x84df;
export const GL_ACTIVE_TEXTURE_ARB = 0x84e0;
export const GL_CLIENT_ACTIVE_TEXTURE_ARB = 0x84e1;
export const GL_MAX_TEXTURE_UNITS_ARB = 0x84e2;
export const GL_DEPTH_STENCIL_MESA = 0x8750;
export const GL_UNSIGNED_INT_24_8_MESA = 0x8751;
export const GL_UNSIGNED_INT_8_24_REV_MESA = 0x8752;
export const GL_UNSIGNED_SHORT_15_1_MESA = 0x8753;
export const GL_UNSIGNED_SHORT_1_15_REV_MESA = 0x8754;
export const GL_ALPHA_BLEND_EQUATION_ATI = 0x883d;
export const GL_OES_EGL_image = 1;

const libglad = dlopen('libglad.so', RTLD_NOW);
let loaded;

export function gladGetProcAddress(name) {
  let addr = dlsym(libglad, 'glad_' + name);
  let buffer = toArrayBuffer(addr, pointerSize);
  let ptr = pointerSize == 8 ? new BigUint64Array(buffer) : new Uint32Array(buffer);
  let ret = '0x' + ptr[0].toString(16);
  //console.log('ret', ret);
  return ret;
}

define('gladLoadGL', dlsym(libglad, 'gladLoadGL'), null, 'int');

export function gladLoadGL() {
  let ret = call('gladLoadGL');
  //if(ret) throw new Error(`gladLoadGL failed: ${ret}`);
  //
  define('glAccum', gladGetProcAddress('glAccum'), null, 'void', 'unsigned int', 'float');
  define('glAlphaFunc', gladGetProcAddress('glAlphaFunc'), null, 'void', 'unsigned int', 'float');
  define('glArrayElement', gladGetProcAddress('glArrayElement'), null, 'void', 'int');
  define('glBegin', gladGetProcAddress('glBegin'), null, 'void', 'unsigned int');
  define('glEnd', gladGetProcAddress('glEnd'), null, 'void');
  define('glFlush', gladGetProcAddress('glFlush'), null, 'void');
  define('glLoadIdentity', gladGetProcAddress('glLoadIdentity'), null, 'void');
  define('glPushMatrix', gladGetProcAddress('glPushMatrix'), null, 'void');
  define('glPopMatrix', gladGetProcAddress('glPopMatrix'), null, 'void');
  define('glBindTexture', gladGetProcAddress('glBindTexture'), null, 'void', 'unsigned int', 'unsigned int');
  define('glBitmap', gladGetProcAddress('glBitmap'), null, 'void', 'int', 'int', 'float', 'float', 'float', 'float', 'void *');
  define('glBlendFunc', gladGetProcAddress('glBlendFunc'), null, 'void', 'unsigned int', 'unsigned int');
  define('glCallList', gladGetProcAddress('glCallList'), null, 'void', 'unsigned int');
  define('glCallLists', gladGetProcAddress('glCallLists'), null, 'void', 'int', 'unsigned int', 'void *');
  define('glClear', gladGetProcAddress('glClear'), null, 'void', 'unsigned int');
  define('glClearAccum', gladGetProcAddress('glClearAccum'), null, 'void', 'float', 'float', 'float', 'float');
  define('glClearColor', gladGetProcAddress('glClearColor'), null, 'void', 'float', 'float', 'float', 'float');
  define('glClearDepth', gladGetProcAddress('glClearDepth'), null, 'void', 'double');
  define('glClearIndex', gladGetProcAddress('glClearIndex'), null, 'void', 'float');
  define('glClearStencil', gladGetProcAddress('glClearStencil'), null, 'void', 'int');
  define('glClipPlane', gladGetProcAddress('glClipPlane'), null, 'void', 'unsigned int', 'void *');
  define('glColor3b', gladGetProcAddress('glColor3b'), null, 'void', 'sint8', 'sint8', 'sint8');
  define('glColor3bv', gladGetProcAddress('glColor3bv'), null, 'void', 'void *');
  define('glColor3d', gladGetProcAddress('glColor3d'), null, 'void', 'double', 'double', 'double');
  define('glColor3dv', gladGetProcAddress('glColor3dv'), null, 'void', 'void *');
  define('glColor3f', gladGetProcAddress('glColor3f'), null, 'void', 'float', 'float', 'float');
  define('glColor3fv', gladGetProcAddress('glColor3fv'), null, 'void', 'void *');
  define('glColor3i', gladGetProcAddress('glColor3i'), null, 'void', 'int', 'int', 'int');
  define('glColor3iv', gladGetProcAddress('glColor3iv'), null, 'void', 'void *');
  define('glColor3s', gladGetProcAddress('glColor3s'), null, 'void', 'short', 'short', 'short');
  define('glColor3sv', gladGetProcAddress('glColor3sv'), null, 'void', 'void *');
  define('glColor3ub', gladGetProcAddress('glColor3ub'), null, 'void', 'unsigned char', 'unsigned char', 'unsigned char');
  define('glColor3ubv', gladGetProcAddress('glColor3ubv'), null, 'void', 'void *');
  define('glColor3ui', gladGetProcAddress('glColor3ui'), null, 'void', 'unsigned int', 'unsigned int', 'unsigned int');
  define('glColor3uiv', gladGetProcAddress('glColor3uiv'), null, 'void', 'void *');
  define('glColor3us', gladGetProcAddress('glColor3us'), null, 'void', 'uint16', 'uint16', 'uint16');
  define('glColor3usv', gladGetProcAddress('glColor3usv'), null, 'void', 'void *');
  define('glColor4b', gladGetProcAddress('glColor4b'), null, 'void', 'sint8', 'sint8', 'sint8', 'sint8');
  define('glColor4bv', gladGetProcAddress('glColor4bv'), null, 'void', 'void *');
  define('glColor4d', gladGetProcAddress('glColor4d'), null, 'void', 'double', 'double', 'double', 'double');
  define('glColor4dv', gladGetProcAddress('glColor4dv'), null, 'void', 'void *');
  define('glColor4f', gladGetProcAddress('glColor4f'), null, 'void', 'float', 'float', 'float', 'float');
  define('glColor4fv', gladGetProcAddress('glColor4fv'), null, 'void', 'void *');
  define('glColor4i', gladGetProcAddress('glColor4i'), null, 'void', 'int', 'int', 'int', 'int');
  define('glColor4iv', gladGetProcAddress('glColor4iv'), null, 'void', 'void *');
  define('glColor4s', gladGetProcAddress('glColor4s'), null, 'void', 'short', 'short', 'short', 'short');
  define('glColor4sv', gladGetProcAddress('glColor4sv'), null, 'void', 'void *');
  define('glColor4ub', gladGetProcAddress('glColor4ub'), null, 'void', 'unsigned char', 'unsigned char', 'unsigned char', 'unsigned char');
  define('glColor4ubv', gladGetProcAddress('glColor4ubv'), null, 'void', 'void *');
  define('glColor4ui', gladGetProcAddress('glColor4ui'), null, 'void', 'unsigned int', 'unsigned int', 'unsigned int', 'unsigned int');
  define('glColor4uiv', gladGetProcAddress('glColor4uiv'), null, 'void', 'void *');
  define('glColor4us', gladGetProcAddress('glColor4us'), null, 'void', 'uint16', 'uint16', 'uint16', 'uint16');
  define('glColor4usv', gladGetProcAddress('glColor4usv'), null, 'void', 'void *');
  define('glColorMask', gladGetProcAddress('glColorMask'), null, 'void', 'unsigned char', 'unsigned char', 'unsigned char', 'unsigned char');
  define('glColorMaterial', gladGetProcAddress('glColorMaterial'), null, 'void', 'unsigned int', 'unsigned int');
  define('glColorPointer', gladGetProcAddress('glColorPointer'), null, 'void', 'int', 'unsigned int', 'int', 'void *');
  define('glCopyPixels', gladGetProcAddress('glCopyPixels'), null, 'void', 'int', 'int', 'int', 'int', 'unsigned int');
  define('glCopyTexImage1D', gladGetProcAddress('glCopyTexImage1D'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'int', 'int', 'int', 'int');
  define('glCopyTexImage2D', gladGetProcAddress('glCopyTexImage2D'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'int', 'int', 'int', 'int', 'int');
  define('glCopyTexSubImage1D', gladGetProcAddress('glCopyTexSubImage1D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int', 'int');
  define('glCopyTexSubImage2D', gladGetProcAddress('glCopyTexSubImage2D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int', 'int', 'int', 'int');
  define('glCullFace', gladGetProcAddress('glCullFace'), null, 'void', 'unsigned int');
  define('glDeleteLists', gladGetProcAddress('glDeleteLists'), null, 'void', 'unsigned int', 'int');
  define('glDeleteTextures', gladGetProcAddress('glDeleteTextures'), null, 'void', 'int', 'void *');
  define('glDepthFunc', gladGetProcAddress('glDepthFunc'), null, 'void', 'unsigned int');
  define('glDepthMask', gladGetProcAddress('glDepthMask'), null, 'void', 'unsigned char');
  define('glDepthRange', gladGetProcAddress('glDepthRange'), null, 'void', 'double', 'double');
  define('glDisable', gladGetProcAddress('glDisable'), null, 'void', 'unsigned int');
  define('glDisableClientState', gladGetProcAddress('glDisableClientState'), null, 'void', 'unsigned int');
  define('glDrawArrays', gladGetProcAddress('glDrawArrays'), null, 'void', 'unsigned int', 'int', 'int');
  define('glDrawBuffer', gladGetProcAddress('glDrawBuffer'), null, 'void', 'unsigned int');
  define('glDrawElements', gladGetProcAddress('glDrawElements'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'void *');
  define('glDrawPixels', gladGetProcAddress('glDrawPixels'), null, 'void', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glEdgeFlag', gladGetProcAddress('glEdgeFlag'), null, 'void', 'unsigned char');
  define('glEdgeFlagPointer', gladGetProcAddress('glEdgeFlagPointer'), null, 'void', 'int', 'void *');
  define('glEdgeFlagv', gladGetProcAddress('glEdgeFlagv'), null, 'void', 'void *');
  define('glEnable', gladGetProcAddress('glEnable'), null, 'void', 'unsigned int');
  define('glEnableClientState', gladGetProcAddress('glEnableClientState'), null, 'void', 'unsigned int');
  define('glEvalCoord1d', gladGetProcAddress('glEvalCoord1d'), null, 'void', 'double');
  define('glEvalCoord1dv', gladGetProcAddress('glEvalCoord1dv'), null, 'void', 'void *');
  define('glEvalCoord1f', gladGetProcAddress('glEvalCoord1f'), null, 'void', 'float');
  define('glEvalCoord1fv', gladGetProcAddress('glEvalCoord1fv'), null, 'void', 'void *');
  define('glEvalCoord2d', gladGetProcAddress('glEvalCoord2d'), null, 'void', 'double', 'double');
  define('glEvalCoord2dv', gladGetProcAddress('glEvalCoord2dv'), null, 'void', 'void *');
  define('glEvalCoord2f', gladGetProcAddress('glEvalCoord2f'), null, 'void', 'float', 'float');
  define('glEvalCoord2fv', gladGetProcAddress('glEvalCoord2fv'), null, 'void', 'void *');
  define('glEvalMesh1', gladGetProcAddress('glEvalMesh1'), null, 'void', 'unsigned int', 'int', 'int');
  define('glEvalMesh2', gladGetProcAddress('glEvalMesh2'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int');
  define('glEvalPoint1', gladGetProcAddress('glEvalPoint1'), null, 'void', 'int');
  define('glEvalPoint2', gladGetProcAddress('glEvalPoint2'), null, 'void', 'int', 'int');
  define('glFeedbackBuffer', gladGetProcAddress('glFeedbackBuffer'), null, 'void', 'int', 'unsigned int', 'void *');
  define('glFogf', gladGetProcAddress('glFogf'), null, 'void', 'unsigned int', 'float');
  define('glFogfv', gladGetProcAddress('glFogfv'), null, 'void', 'unsigned int', 'void *');
  define('glFogi', gladGetProcAddress('glFogi'), null, 'void', 'unsigned int', 'int');
  define('glFogiv', gladGetProcAddress('glFogiv'), null, 'void', 'unsigned int', 'void *');
  define('glFrontFace', gladGetProcAddress('glFrontFace'), null, 'void', 'unsigned int');
  define('glFrustum', gladGetProcAddress('glFrustum'), null, 'void', 'double', 'double', 'double', 'double', 'double', 'double');
  define('glGenLists', gladGetProcAddress('glGenLists'), null, 'unsigned int', 'int');
  define('glGenTextures', gladGetProcAddress('glGenTextures'), null, 'void', 'int', 'void *');
  define('glGetBooleanv', gladGetProcAddress('glGetBooleanv'), null, 'void', 'unsigned int', 'void *');
  define('glGetClipPlane', gladGetProcAddress('glGetClipPlane'), null, 'void', 'unsigned int', 'void *');
  define('glGetDoublev', gladGetProcAddress('glGetDoublev'), null, 'void', 'unsigned int', 'void *');
  define('glGetFloatv', gladGetProcAddress('glGetFloatv'), null, 'void', 'unsigned int', 'void *');
  define('glGetIntegerv', gladGetProcAddress('glGetIntegerv'), null, 'void', 'unsigned int', 'void *');
  define('glGetLightfv', gladGetProcAddress('glGetLightfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetLightiv', gladGetProcAddress('glGetLightiv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetMapdv', gladGetProcAddress('glGetMapdv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetMapfv', gladGetProcAddress('glGetMapfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetMapiv', gladGetProcAddress('glGetMapiv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetMaterialfv', gladGetProcAddress('glGetMaterialfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetMaterialiv', gladGetProcAddress('glGetMaterialiv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetPixelMapfv', gladGetProcAddress('glGetPixelMapfv'), null, 'void', 'unsigned int', 'void *');
  define('glGetPixelMapuiv', gladGetProcAddress('glGetPixelMapuiv'), null, 'void', 'unsigned int', 'void *');
  define('glGetPixelMapusv', gladGetProcAddress('glGetPixelMapusv'), null, 'void', 'unsigned int', 'void *');
  define('glGetPointerv', gladGetProcAddress('glGetPointerv'), null, 'void', 'unsigned int', 'void *');
  define('glGetPolygonStipple', gladGetProcAddress('glGetPolygonStipple'), null, 'void', 'void *');
  define('glGetString', gladGetProcAddress('glGetString'), null, 'void *', 'unsigned int');
  define('glGetTexEnvfv', gladGetProcAddress('glGetTexEnvfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexEnviv', gladGetProcAddress('glGetTexEnviv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexGendv', gladGetProcAddress('glGetTexGendv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexGenfv', gladGetProcAddress('glGetTexGenfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexGeniv', gladGetProcAddress('glGetTexGeniv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexImage', gladGetProcAddress('glGetTexImage'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexLevelParameterfv', gladGetProcAddress('glGetTexLevelParameterfv'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'void *');
  define('glGetTexLevelParameteriv', gladGetProcAddress('glGetTexLevelParameteriv'), null, 'void', 'unsigned int', 'int', 'unsigned int', 'void *');
  define('glGetTexParameterfv', gladGetProcAddress('glGetTexParameterfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glGetTexParameteriv', gladGetProcAddress('glGetTexParameteriv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glHint', gladGetProcAddress('glHint'), null, 'void', 'unsigned int', 'unsigned int');
  define('glIndexd', gladGetProcAddress('glIndexd'), null, 'void', 'double');
  define('glIndexdv', gladGetProcAddress('glIndexdv'), null, 'void', 'void *');
  define('glIndexf', gladGetProcAddress('glIndexf'), null, 'void', 'float');
  define('glIndexfv', gladGetProcAddress('glIndexfv'), null, 'void', 'void *');
  define('glIndexi', gladGetProcAddress('glIndexi'), null, 'void', 'int');
  define('glIndexiv', gladGetProcAddress('glIndexiv'), null, 'void', 'void *');
  define('glIndexMask', gladGetProcAddress('glIndexMask'), null, 'void', 'unsigned int');
  define('glIndexPointer', gladGetProcAddress('glIndexPointer'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glIndexs', gladGetProcAddress('glIndexs'), null, 'void', 'short');
  define('glIndexsv', gladGetProcAddress('glIndexsv'), null, 'void', 'void *');
  define('glIndexub', gladGetProcAddress('glIndexub'), null, 'void', 'unsigned char');
  define('glIndexubv', gladGetProcAddress('glIndexubv'), null, 'void', 'void *');
  define('glInterleavedArrays', gladGetProcAddress('glInterleavedArrays'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glIsEnabled', gladGetProcAddress('glIsEnabled'), null, 'unsigned char', 'unsigned int');
  define('glIsList', gladGetProcAddress('glIsList'), null, 'unsigned char', 'unsigned int');
  define('glIsTexture', gladGetProcAddress('glIsTexture'), null, 'unsigned char', 'unsigned int');
  define('glLightf', gladGetProcAddress('glLightf'), null, 'void', 'unsigned int', 'unsigned int', 'float');
  define('glLightfv', gladGetProcAddress('glLightfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glLighti', gladGetProcAddress('glLighti'), null, 'void', 'unsigned int', 'unsigned int', 'int');
  define('glLightiv', gladGetProcAddress('glLightiv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glLightModelf', gladGetProcAddress('glLightModelf'), null, 'void', 'unsigned int', 'float');
  define('glLightModelfv', gladGetProcAddress('glLightModelfv'), null, 'void', 'unsigned int', 'void *');
  define('glLightModeli', gladGetProcAddress('glLightModeli'), null, 'void', 'unsigned int', 'int');
  define('glLightModeliv', gladGetProcAddress('glLightModeliv'), null, 'void', 'unsigned int', 'void *');
  define('glLineStipple', gladGetProcAddress('glLineStipple'), null, 'void', 'int', 'uint16');
  define('glLineWidth', gladGetProcAddress('glLineWidth'), null, 'void', 'float');
  define('glListBase', gladGetProcAddress('glListBase'), null, 'void', 'unsigned int');
  define('glLoadMatrixd', gladGetProcAddress('glLoadMatrixd'), null, 'void', 'void *');
  define('glLoadMatrixf', gladGetProcAddress('glLoadMatrixf'), null, 'void', 'void *');
  define('glLoadName', gladGetProcAddress('glLoadName'), null, 'void', 'unsigned int');
  define('glLogicOp', gladGetProcAddress('glLogicOp'), null, 'void', 'unsigned int');
  define('glMap1d', gladGetProcAddress('glMap1d'), null, 'void', 'unsigned int', 'double', 'double', 'int', 'int', 'void *');
  define('glMap1f', gladGetProcAddress('glMap1f'), null, 'void', 'unsigned int', 'float', 'float', 'int', 'int', 'void *');
  define('glMap2d', gladGetProcAddress('glMap2d'), null, 'void', 'unsigned int', 'double', 'double', 'int', 'int', 'double', 'double', 'int', 'int', 'void *');
  define('glMap2f', gladGetProcAddress('glMap2f'), null, 'void', 'unsigned int', 'float', 'float', 'int', 'int', 'float', 'float', 'int', 'int', 'void *');
  define('glMapGrid1d', gladGetProcAddress('glMapGrid1d'), null, 'void', 'int', 'double', 'double');
  define('glMapGrid1f', gladGetProcAddress('glMapGrid1f'), null, 'void', 'int', 'float', 'float');
  define('glMapGrid2d', gladGetProcAddress('glMapGrid2d'), null, 'void', 'int', 'double', 'double', 'int', 'double', 'double');
  define('glMapGrid2f', gladGetProcAddress('glMapGrid2f'), null, 'void', 'int', 'float', 'float', 'int', 'float', 'float');
  define('glMaterialf', gladGetProcAddress('glMaterialf'), null, 'void', 'unsigned int', 'unsigned int', 'float');
  define('glMaterialfv', gladGetProcAddress('glMaterialfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glMateriali', gladGetProcAddress('glMateriali'), null, 'void', 'unsigned int', 'unsigned int', 'int');
  define('glMaterialiv', gladGetProcAddress('glMaterialiv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glMatrixMode', gladGetProcAddress('glMatrixMode'), null, 'void', 'unsigned int');
  define('glMultMatrixd', gladGetProcAddress('glMultMatrixd'), null, 'void', 'void *');
  define('glMultMatrixf', gladGetProcAddress('glMultMatrixf'), null, 'void', 'void *');
  define('glNewList', gladGetProcAddress('glNewList'), null, 'void', 'unsigned int', 'unsigned int');
  define('glNormal3b', gladGetProcAddress('glNormal3b'), null, 'void', 'sint8', 'sint8', 'sint8');
  define('glNormal3bv', gladGetProcAddress('glNormal3bv'), null, 'void', 'void *');
  define('glNormal3d', gladGetProcAddress('glNormal3d'), null, 'void', 'double', 'double', 'double');
  define('glNormal3dv', gladGetProcAddress('glNormal3dv'), null, 'void', 'void *');
  define('glNormal3f', gladGetProcAddress('glNormal3f'), null, 'void', 'float', 'float', 'float');
  define('glNormal3fv', gladGetProcAddress('glNormal3fv'), null, 'void', 'void *');
  define('glNormal3i', gladGetProcAddress('glNormal3i'), null, 'void', 'int', 'int', 'int');
  define('glNormal3iv', gladGetProcAddress('glNormal3iv'), null, 'void', 'void *');
  define('glNormal3s', gladGetProcAddress('glNormal3s'), null, 'void', 'short', 'short', 'short');
  define('glNormal3sv', gladGetProcAddress('glNormal3sv'), null, 'void', 'void *');
  define('glNormalPointer', gladGetProcAddress('glNormalPointer'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glOrtho', gladGetProcAddress('glOrtho'), null, 'void', 'double', 'double', 'double', 'double', 'double', 'double');
  define('glPassThrough', gladGetProcAddress('glPassThrough'), null, 'void', 'float');
  define('glPixelMapfv', gladGetProcAddress('glPixelMapfv'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glPixelMapuiv', gladGetProcAddress('glPixelMapuiv'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glPixelMapusv', gladGetProcAddress('glPixelMapusv'), null, 'void', 'unsigned int', 'int', 'void *');
  define('glPixelStoref', gladGetProcAddress('glPixelStoref'), null, 'void', 'unsigned int', 'float');
  define('glPixelStorei', gladGetProcAddress('glPixelStorei'), null, 'void', 'unsigned int', 'int');
  define('glPixelTransferf', gladGetProcAddress('glPixelTransferf'), null, 'void', 'unsigned int', 'float');
  define('glPixelTransferi', gladGetProcAddress('glPixelTransferi'), null, 'void', 'unsigned int', 'int');
  define('glPixelZoom', gladGetProcAddress('glPixelZoom'), null, 'void', 'float', 'float');
  define('glPointSize', gladGetProcAddress('glPointSize'), null, 'void', 'float');
  define('glPolygonMode', gladGetProcAddress('glPolygonMode'), null, 'void', 'unsigned int', 'unsigned int');
  define('glPolygonOffset', gladGetProcAddress('glPolygonOffset'), null, 'void', 'float', 'float');
  define('glPolygonStipple', gladGetProcAddress('glPolygonStipple'), null, 'void', 'void *');
  define('glPrioritizeTextures', gladGetProcAddress('glPrioritizeTextures'), null, 'void', 'int', 'void *', 'void *');
  define('glPushAttrib', gladGetProcAddress('glPushAttrib'), null, 'void', 'unsigned int');
  define('glPushClientAttrib', gladGetProcAddress('glPushClientAttrib'), null, 'void', 'unsigned int');
  define('glPushName', gladGetProcAddress('glPushName'), null, 'void', 'unsigned int');
  define('glRasterPos2d', gladGetProcAddress('glRasterPos2d'), null, 'void', 'double', 'double');
  define('glRasterPos2dv', gladGetProcAddress('glRasterPos2dv'), null, 'void', 'void *');
  define('glRasterPos2f', gladGetProcAddress('glRasterPos2f'), null, 'void', 'float', 'float');
  define('glRasterPos2fv', gladGetProcAddress('glRasterPos2fv'), null, 'void', 'void *');
  define('glRasterPos2i', gladGetProcAddress('glRasterPos2i'), null, 'void', 'int', 'int');
  define('glRasterPos2iv', gladGetProcAddress('glRasterPos2iv'), null, 'void', 'void *');
  define('glRasterPos2s', gladGetProcAddress('glRasterPos2s'), null, 'void', 'short', 'short');
  define('glRasterPos2sv', gladGetProcAddress('glRasterPos2sv'), null, 'void', 'void *');
  define('glRasterPos3d', gladGetProcAddress('glRasterPos3d'), null, 'void', 'double', 'double', 'double');
  define('glRasterPos3dv', gladGetProcAddress('glRasterPos3dv'), null, 'void', 'void *');
  define('glRasterPos3f', gladGetProcAddress('glRasterPos3f'), null, 'void', 'float', 'float', 'float');
  define('glRasterPos3fv', gladGetProcAddress('glRasterPos3fv'), null, 'void', 'void *');
  define('glRasterPos3i', gladGetProcAddress('glRasterPos3i'), null, 'void', 'int', 'int', 'int');
  define('glRasterPos3iv', gladGetProcAddress('glRasterPos3iv'), null, 'void', 'void *');
  define('glRasterPos3s', gladGetProcAddress('glRasterPos3s'), null, 'void', 'short', 'short', 'short');
  define('glRasterPos3sv', gladGetProcAddress('glRasterPos3sv'), null, 'void', 'void *');
  define('glRasterPos4d', gladGetProcAddress('glRasterPos4d'), null, 'void', 'double', 'double', 'double', 'double');
  define('glRasterPos4dv', gladGetProcAddress('glRasterPos4dv'), null, 'void', 'void *');
  define('glRasterPos4f', gladGetProcAddress('glRasterPos4f'), null, 'void', 'float', 'float', 'float', 'float');
  define('glRasterPos4fv', gladGetProcAddress('glRasterPos4fv'), null, 'void', 'void *');
  define('glRasterPos4i', gladGetProcAddress('glRasterPos4i'), null, 'void', 'int', 'int', 'int', 'int');
  define('glRasterPos4iv', gladGetProcAddress('glRasterPos4iv'), null, 'void', 'void *');
  define('glRasterPos4s', gladGetProcAddress('glRasterPos4s'), null, 'void', 'short', 'short', 'short', 'short');
  define('glRasterPos4sv', gladGetProcAddress('glRasterPos4sv'), null, 'void', 'void *');
  define('glReadBuffer', gladGetProcAddress('glReadBuffer'), null, 'void', 'unsigned int');
  define('glReadPixels', gladGetProcAddress('glReadPixels'), null, 'void', 'int', 'int', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glRectd', gladGetProcAddress('glRectd'), null, 'void', 'double', 'double', 'double', 'double');
  define('glRectdv', gladGetProcAddress('glRectdv'), null, 'void', 'void *', 'void *');
  define('glRectf', gladGetProcAddress('glRectf'), null, 'void', 'float', 'float', 'float', 'float');
  define('glRectfv', gladGetProcAddress('glRectfv'), null, 'void', 'void *', 'void *');
  define('glRecti', gladGetProcAddress('glRecti'), null, 'void', 'int', 'int', 'int', 'int');
  define('glRectiv', gladGetProcAddress('glRectiv'), null, 'void', 'void *', 'void *');
  define('glRects', gladGetProcAddress('glRects'), null, 'void', 'short', 'short', 'short', 'short');
  define('glRectsv', gladGetProcAddress('glRectsv'), null, 'void', 'void *', 'void *');
  define('glRenderMode', gladGetProcAddress('glRenderMode'), null, 'int', 'unsigned int');
  define('glRotated', gladGetProcAddress('glRotated'), null, 'void', 'double', 'double', 'double', 'double');
  define('glRotatef', gladGetProcAddress('glRotatef'), null, 'void', 'float', 'float', 'float', 'float');
  define('glScaled', gladGetProcAddress('glScaled'), null, 'void', 'double', 'double', 'double');
  define('glScalef', gladGetProcAddress('glScalef'), null, 'void', 'float', 'float', 'float');
  define('glScissor', gladGetProcAddress('glScissor'), null, 'void', 'int', 'int', 'int', 'int');
  define('glSelectBuffer', gladGetProcAddress('glSelectBuffer'), null, 'void', 'int', 'void *');
  define('glShadeModel', gladGetProcAddress('glShadeModel'), null, 'void', 'unsigned int');
  define('glStencilFunc', gladGetProcAddress('glStencilFunc'), null, 'void', 'unsigned int', 'int', 'unsigned int');
  define('glStencilMask', gladGetProcAddress('glStencilMask'), null, 'void', 'unsigned int');
  define('glStencilOp', gladGetProcAddress('glStencilOp'), null, 'void', 'unsigned int', 'unsigned int', 'unsigned int');
  define('glTexCoord1d', gladGetProcAddress('glTexCoord1d'), null, 'void', 'double');
  define('glTexCoord1dv', gladGetProcAddress('glTexCoord1dv'), null, 'void', 'void *');
  define('glTexCoord1f', gladGetProcAddress('glTexCoord1f'), null, 'void', 'float');
  define('glTexCoord1fv', gladGetProcAddress('glTexCoord1fv'), null, 'void', 'void *');
  define('glTexCoord1i', gladGetProcAddress('glTexCoord1i'), null, 'void', 'int');
  define('glTexCoord1iv', gladGetProcAddress('glTexCoord1iv'), null, 'void', 'void *');
  define('glTexCoord1s', gladGetProcAddress('glTexCoord1s'), null, 'void', 'short');
  define('glTexCoord1sv', gladGetProcAddress('glTexCoord1sv'), null, 'void', 'void *');
  define('glTexCoord2d', gladGetProcAddress('glTexCoord2d'), null, 'void', 'double', 'double');
  define('glTexCoord2dv', gladGetProcAddress('glTexCoord2dv'), null, 'void', 'void *');
  define('glTexCoord2f', gladGetProcAddress('glTexCoord2f'), null, 'void', 'float', 'float');
  define('glTexCoord2fv', gladGetProcAddress('glTexCoord2fv'), null, 'void', 'void *');
  define('glTexCoord2i', gladGetProcAddress('glTexCoord2i'), null, 'void', 'int', 'int');
  define('glTexCoord2iv', gladGetProcAddress('glTexCoord2iv'), null, 'void', 'void *');
  define('glTexCoord2s', gladGetProcAddress('glTexCoord2s'), null, 'void', 'short', 'short');
  define('glTexCoord2sv', gladGetProcAddress('glTexCoord2sv'), null, 'void', 'void *');
  define('glTexCoord3d', gladGetProcAddress('glTexCoord3d'), null, 'void', 'double', 'double', 'double');
  define('glTexCoord3dv', gladGetProcAddress('glTexCoord3dv'), null, 'void', 'void *');
  define('glTexCoord3f', gladGetProcAddress('glTexCoord3f'), null, 'void', 'float', 'float', 'float');
  define('glTexCoord3fv', gladGetProcAddress('glTexCoord3fv'), null, 'void', 'void *');
  define('glTexCoord3i', gladGetProcAddress('glTexCoord3i'), null, 'void', 'int', 'int', 'int');
  define('glTexCoord3iv', gladGetProcAddress('glTexCoord3iv'), null, 'void', 'void *');
  define('glTexCoord3s', gladGetProcAddress('glTexCoord3s'), null, 'void', 'short', 'short', 'short');
  define('glTexCoord3sv', gladGetProcAddress('glTexCoord3sv'), null, 'void', 'void *');
  define('glTexCoord4d', gladGetProcAddress('glTexCoord4d'), null, 'void', 'double', 'double', 'double', 'double');
  define('glTexCoord4dv', gladGetProcAddress('glTexCoord4dv'), null, 'void', 'void *');
  define('glTexCoord4f', gladGetProcAddress('glTexCoord4f'), null, 'void', 'float', 'float', 'float', 'float');
  define('glTexCoord4fv', gladGetProcAddress('glTexCoord4fv'), null, 'void', 'void *');
  define('glTexCoord4i', gladGetProcAddress('glTexCoord4i'), null, 'void', 'int', 'int', 'int', 'int');
  define('glTexCoord4iv', gladGetProcAddress('glTexCoord4iv'), null, 'void', 'void *');
  define('glTexCoord4s', gladGetProcAddress('glTexCoord4s'), null, 'void', 'short', 'short', 'short', 'short');
  define('glTexCoord4sv', gladGetProcAddress('glTexCoord4sv'), null, 'void', 'void *');
  define('glTexCoordPointer', gladGetProcAddress('glTexCoordPointer'), null, 'void', 'int', 'unsigned int', 'int', 'void *');
  define('glTexEnvf', gladGetProcAddress('glTexEnvf'), null, 'void', 'unsigned int', 'unsigned int', 'float');
  define('glTexEnvfv', gladGetProcAddress('glTexEnvfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexEnvi', gladGetProcAddress('glTexEnvi'), null, 'void', 'unsigned int', 'unsigned int', 'int');
  define('glTexEnviv', gladGetProcAddress('glTexEnviv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexGend', gladGetProcAddress('glTexGend'), null, 'void', 'unsigned int', 'unsigned int', 'double');
  define('glTexGendv', gladGetProcAddress('glTexGendv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexGenf', gladGetProcAddress('glTexGenf'), null, 'void', 'unsigned int', 'unsigned int', 'float');
  define('glTexGenfv', gladGetProcAddress('glTexGenfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexGeni', gladGetProcAddress('glTexGeni'), null, 'void', 'unsigned int', 'unsigned int', 'int');
  define('glTexGeniv', gladGetProcAddress('glTexGeniv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexImage1D', gladGetProcAddress('glTexImage1D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glTexImage2D', gladGetProcAddress('glTexImage2D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glTexParameterf', gladGetProcAddress('glTexParameterf'), null, 'void', 'unsigned int', 'unsigned int', 'float');
  define('glTexParameterfv', gladGetProcAddress('glTexParameterfv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexParameteri', gladGetProcAddress('glTexParameteri'), null, 'void', 'unsigned int', 'unsigned int', 'int');
  define('glTexParameteriv', gladGetProcAddress('glTexParameteriv'), null, 'void', 'unsigned int', 'unsigned int', 'void *');
  define('glTexSubImage1D', gladGetProcAddress('glTexSubImage1D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glTexSubImage2D', gladGetProcAddress('glTexSubImage2D'), null, 'void', 'unsigned int', 'int', 'int', 'int', 'int', 'int', 'unsigned int', 'unsigned int', 'void *');
  define('glTranslated', gladGetProcAddress('glTranslated'), null, 'void', 'double', 'double', 'double');
  define('glTranslatef', gladGetProcAddress('glTranslatef'), null, 'void', 'float', 'float', 'float');
  define('glVertex2d', gladGetProcAddress('glVertex2d'), null, 'void', 'double', 'double');
  define('glVertex2dv', gladGetProcAddress('glVertex2dv'), null, 'void', 'void *');
  define('glVertex2f', gladGetProcAddress('glVertex2f'), null, 'void', 'float', 'float');
  define('glVertex2fv', gladGetProcAddress('glVertex2fv'), null, 'void', 'void *');
  define('glVertex2i', gladGetProcAddress('glVertex2i'), null, 'void', 'int', 'int');
  define('glVertex2iv', gladGetProcAddress('glVertex2iv'), null, 'void', 'void *');
  define('glVertex2s', gladGetProcAddress('glVertex2s'), null, 'void', 'short', 'short');
  define('glVertex2sv', gladGetProcAddress('glVertex2sv'), null, 'void', 'void *');
  define('glVertex3d', gladGetProcAddress('glVertex3d'), null, 'void', 'double', 'double', 'double');
  define('glVertex3dv', gladGetProcAddress('glVertex3dv'), null, 'void', 'void *');
  define('glVertex3f', gladGetProcAddress('glVertex3f'), null, 'void', 'float', 'float', 'float');
  define('glVertex3fv', gladGetProcAddress('glVertex3fv'), null, 'void', 'void *');
  define('glVertex3i', gladGetProcAddress('glVertex3i'), null, 'void', 'int', 'int', 'int');
  define('glVertex3iv', gladGetProcAddress('glVertex3iv'), null, 'void', 'void *');
  define('glVertex3s', gladGetProcAddress('glVertex3s'), null, 'void', 'short', 'short', 'short');
  define('glVertex3sv', gladGetProcAddress('glVertex3sv'), null, 'void', 'void *');
  define('glVertex4d', gladGetProcAddress('glVertex4d'), null, 'void', 'double', 'double', 'double', 'double');
  define('glVertex4dv', gladGetProcAddress('glVertex4dv'), null, 'void', 'void *');
  define('glVertex4f', gladGetProcAddress('glVertex4f'), null, 'void', 'float', 'float', 'float', 'float');
  define('glVertex4fv', gladGetProcAddress('glVertex4fv'), null, 'void', 'void *');
  define('glVertex4i', gladGetProcAddress('glVertex4i'), null, 'void', 'int', 'int', 'int', 'int');
  define('glVertex4iv', gladGetProcAddress('glVertex4iv'), null, 'void', 'void *');
  define('glVertex4s', gladGetProcAddress('glVertex4s'), null, 'void', 'short', 'short', 'short', 'short');
  define('glVertex4sv', gladGetProcAddress('glVertex4sv'), null, 'void', 'void *');
  define('glVertexPointer', gladGetProcAddress('glVertexPointer'), null, 'void', 'int', 'unsigned int', 'int', 'void *');
  define('glViewport', gladGetProcAddress('glViewport'), null, 'void', 'int', 'int', 'int', 'int');

  return ret;
}

export function glAccum(op, value) {
  return call('glAccum', op, value);
}

export function glAlphaFunc(func, ref) {
  return call('glAlphaFunc', func, ref);
}

export function glArrayElement(i) {
  return call('glArrayElement', i);
}

export function glBegin(mode) {
  return call('glBegin', mode);
}

export function glEnd() {
  return call('glEnd');
}

export function glFlush() {
  return call('glFlush');
}

export function glLoadIdentity() {
  return call('glLoadIdentity');
}

export function glPushMatrix() {
  return call('glPushMatrix');
}

export function glPopMatrix() {
  return call('glPopMatrix');
}

export function glBindTexture(target, texture) {
  return call('glBindTexture', target, texture);
}

export function glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap) {
  return call('glBitmap', width, height, xorig, yorig, xmove, ymove, bitmap);
}

export function glBlendFunc(sfactor, dfactor) {
  return call('glBlendFunc', sfactor, dfactor);
}

export function glCallList(list) {
  return call('glCallList', list);
}

export function glCallLists(n, type, lists) {
  return call('glCallLists', n, type, lists);
}

export function glClear(mask) {
  return call('glClear', mask);
}

export function glClearAccum(red, green, blue, alpha) {
  return call('glClearAccum', red, green, blue, alpha);
}

export function glClearColor(red, green, blue, alpha) {
  return call('glClearColor', red, green, blue, alpha);
}

export function glClearDepth(depth) {
  return call('glClearDepth', depth);
}

export function glClearIndex(c) {
  return call('glClearIndex', c);
}

export function glClearStencil(s) {
  return call('glClearStencil', s);
}

export function glClipPlane(plane, equation) {
  return call('glClipPlane', plane, equation);
}

export function glColor3b(red, green, blue) {
  return call('glColor3b', red, green, blue);
}

export function glColor3bv(v) {
  return call('glColor3bv', v);
}

export function glColor3d(red, green, blue) {
  return call('glColor3d', red, green, blue);
}

export function glColor3dv(v) {
  return call('glColor3dv', v);
}

export function glColor3f(red, green, blue) {
  return call('glColor3f', red, green, blue);
}

export function glColor3fv(v) {
  return call('glColor3fv', v);
}

export function glColor3i(red, green, blue) {
  return call('glColor3i', red, green, blue);
}

export function glColor3iv(v) {
  return call('glColor3iv', v);
}

export function glColor3s(red, green, blue) {
  return call('glColor3s', red, green, blue);
}

export function glColor3sv(v) {
  return call('glColor3sv', v);
}

export function glColor3ub(red, green, blue) {
  return call('glColor3ub', red, green, blue);
}

export function glColor3ubv(v) {
  return call('glColor3ubv', v);
}

export function glColor3ui(red, green, blue) {
  return call('glColor3ui', red, green, blue);
}

export function glColor3uiv(v) {
  return call('glColor3uiv', v);
}

export function glColor3us(red, green, blue) {
  return call('glColor3us', red, green, blue);
}

export function glColor3usv(v) {
  return call('glColor3usv', v);
}

export function glColor4b(red, green, blue, alpha) {
  return call('glColor4b', red, green, blue, alpha);
}

export function glColor4bv(v) {
  return call('glColor4bv', v);
}

export function glColor4d(red, green, blue, alpha) {
  return call('glColor4d', red, green, blue, alpha);
}

export function glColor4dv(v) {
  return call('glColor4dv', v);
}

export function glColor4f(red, green, blue, alpha) {
  return call('glColor4f', red, green, blue, alpha);
}

export function glColor4fv(v) {
  return call('glColor4fv', v);
}

export function glColor4i(red, green, blue, alpha) {
  return call('glColor4i', red, green, blue, alpha);
}

export function glColor4iv(v) {
  return call('glColor4iv', v);
}

export function glColor4s(red, green, blue, alpha) {
  return call('glColor4s', red, green, blue, alpha);
}

export function glColor4sv(v) {
  return call('glColor4sv', v);
}

export function glColor4ub(red, green, blue, alpha) {
  return call('glColor4ub', red, green, blue, alpha);
}

export function glColor4ubv(v) {
  return call('glColor4ubv', v);
}

export function glColor4ui(red, green, blue, alpha) {
  return call('glColor4ui', red, green, blue, alpha);
}

export function glColor4uiv(v) {
  return call('glColor4uiv', v);
}

export function glColor4us(red, green, blue, alpha) {
  return call('glColor4us', red, green, blue, alpha);
}

export function glColor4usv(v) {
  return call('glColor4usv', v);
}

export function glColorMask(red, green, blue, alpha) {
  return call('glColorMask', red, green, blue, alpha);
}

export function glColorMaterial(face, mode) {
  return call('glColorMaterial', face, mode);
}

export function glColorPointer(size, type, stride, pointer) {
  return call('glColorPointer', size, type, stride, pointer);
}

export function glCopyPixels(x, y, width, height, type) {
  return call('glCopyPixels', x, y, width, height, type);
}

export function glCopyTexImage1D(target, level, internalFormat, x, y, width, border) {
  return call('glCopyTexImage1D', target, level, internalFormat, x, y, width, border);
}

export function glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border) {
  return call('glCopyTexImage2D', target, level, internalFormat, x, y, width, height, border);
}

export function glCopyTexSubImage1D(target, level, xoffset, x, y, width) {
  return call('glCopyTexSubImage1D', target, level, xoffset, x, y, width);
}

export function glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) {
  return call('glCopyTexSubImage2D', target, level, xoffset, yoffset, x, y, width, height);
}

export function glCullFace(mode) {
  return call('glCullFace', mode);
}

export function glDeleteLists(list, range) {
  return call('glDeleteLists', list, range);
}

export function glDeleteTextures(n, textures) {
  return call('glDeleteTextures', n, textures);
}

export function glDepthFunc(func) {
  return call('glDepthFunc', func);
}

export function glDepthMask(flag) {
  return call('glDepthMask', flag);
}

export function glDepthRange(zNear, zFar) {
  return call('glDepthRange', zNear, zFar);
}

export function glDisable(cap) {
  return call('glDisable', cap);
}

export function glDisableClientState(array) {
  return call('glDisableClientState', array);
}

export function glDrawArrays(mode, first, count) {
  return call('glDrawArrays', mode, first, count);
}

export function glDrawBuffer(mode) {
  return call('glDrawBuffer', mode);
}

export function glDrawElements(mode, count, type, indices) {
  return call('glDrawElements', mode, count, type, indices);
}

export function glDrawPixels(width, height, format, type, pixels) {
  return call('glDrawPixels', width, height, format, type, pixels);
}

export function glEdgeFlag(flag) {
  return call('glEdgeFlag', flag);
}

export function glEdgeFlagPointer(stride, pointer) {
  return call('glEdgeFlagPointer', stride, pointer);
}

export function glEdgeFlagv(flag) {
  return call('glEdgeFlagv', flag);
}

export function glEnable(cap) {
  return call('glEnable', cap);
}

export function glEnableClientState(array) {
  return call('glEnableClientState', array);
}

export function glEvalCoord1d(u) {
  return call('glEvalCoord1d', u);
}

export function glEvalCoord1dv(u) {
  return call('glEvalCoord1dv', u);
}

export function glEvalCoord1f(u) {
  return call('glEvalCoord1f', u);
}

export function glEvalCoord1fv(u) {
  return call('glEvalCoord1fv', u);
}

export function glEvalCoord2d(u, v) {
  return call('glEvalCoord2d', u, v);
}

export function glEvalCoord2dv(u) {
  return call('glEvalCoord2dv', u);
}

export function glEvalCoord2f(u, v) {
  return call('glEvalCoord2f', u, v);
}

export function glEvalCoord2fv(u) {
  return call('glEvalCoord2fv', u);
}

export function glEvalMesh1(mode, i1, i2) {
  return call('glEvalMesh1', mode, i1, i2);
}

export function glEvalMesh2(mode, i1, i2, j1, j2) {
  return call('glEvalMesh2', mode, i1, i2, j1, j2);
}

export function glEvalPoint1(i) {
  return call('glEvalPoint1', i);
}

export function glEvalPoint2(i, j) {
  return call('glEvalPoint2', i, j);
}

export function glFeedbackBuffer(size, type, buffer) {
  return call('glFeedbackBuffer', size, type, buffer);
}

export function glFogf(pname, param) {
  return call('glFogf', pname, param);
}

export function glFogfv(pname, params) {
  return call('glFogfv', pname, params);
}

export function glFogi(pname, param) {
  return call('glFogi', pname, param);
}

export function glFogiv(pname, params) {
  return call('glFogiv', pname, params);
}

export function glFrontFace(mode) {
  return call('glFrontFace', mode);
}

export function glFrustum(left, right, bottom, top, zNear, zFar) {
  return call('glFrustum', left, right, bottom, top, zNear, zFar);
}

export function glGenLists(range) {
  return call('glGenLists', range);
}

export function glGenTextures(n, textures) {
  return call('glGenTextures', n, textures);
}

export function glGetBooleanv(pname, params) {
  return call('glGetBooleanv', pname, params);
}

export function glGetClipPlane(plane, equation) {
  return call('glGetClipPlane', plane, equation);
}

export function glGetDoublev(pname, params) {
  return call('glGetDoublev', pname, params);
}

export function glGetFloatv(pname, params) {
  return call('glGetFloatv', pname, params);
}

export function glGetIntegerv(pname, params) {
  return call('glGetIntegerv', pname, params);
}

export function glGetLightfv(light, pname, params) {
  return call('glGetLightfv', light, pname, params);
}

export function glGetLightiv(light, pname, params) {
  return call('glGetLightiv', light, pname, params);
}

export function glGetMapdv(target, query, v) {
  return call('glGetMapdv', target, query, v);
}

export function glGetMapfv(target, query, v) {
  return call('glGetMapfv', target, query, v);
}

export function glGetMapiv(target, query, v) {
  return call('glGetMapiv', target, query, v);
}

export function glGetMaterialfv(face, pname, params) {
  return call('glGetMaterialfv', face, pname, params);
}

export function glGetMaterialiv(face, pname, params) {
  return call('glGetMaterialiv', face, pname, params);
}

export function glGetPixelMapfv(map, values) {
  return call('glGetPixelMapfv', map, values);
}

export function glGetPixelMapuiv(map, values) {
  return call('glGetPixelMapuiv', map, values);
}

export function glGetPixelMapusv(map, values) {
  return call('glGetPixelMapusv', map, values);
}

export function glGetPointerv(pname, params) {
  return call('glGetPointerv', pname, params);
}

export function glGetPolygonStipple(mask) {
  return call('glGetPolygonStipple', mask);
}

export function glGetString(name) {
  return call('glGetString', name);
}

export function glGetTexEnvfv(target, pname, params) {
  return call('glGetTexEnvfv', target, pname, params);
}

export function glGetTexEnviv(target, pname, params) {
  return call('glGetTexEnviv', target, pname, params);
}

export function glGetTexGendv(coord, pname, params) {
  return call('glGetTexGendv', coord, pname, params);
}

export function glGetTexGenfv(coord, pname, params) {
  return call('glGetTexGenfv', coord, pname, params);
}

export function glGetTexGeniv(coord, pname, params) {
  return call('glGetTexGeniv', coord, pname, params);
}

export function glGetTexImage(target, level, format, type, pixels) {
  return call('glGetTexImage', target, level, format, type, pixels);
}

export function glGetTexLevelParameterfv(target, level, pname, params) {
  return call('glGetTexLevelParameterfv', target, level, pname, params);
}

export function glGetTexLevelParameteriv(target, level, pname, params) {
  return call('glGetTexLevelParameteriv', target, level, pname, params);
}

export function glGetTexParameterfv(target, pname, params) {
  return call('glGetTexParameterfv', target, pname, params);
}

export function glGetTexParameteriv(target, pname, params) {
  return call('glGetTexParameteriv', target, pname, params);
}

export function glHint(target, mode) {
  return call('glHint', target, mode);
}

export function glIndexd(c) {
  return call('glIndexd', c);
}

export function glIndexdv(c) {
  return call('glIndexdv', c);
}

export function glIndexf(c) {
  return call('glIndexf', c);
}

export function glIndexfv(c) {
  return call('glIndexfv', c);
}

export function glIndexi(c) {
  return call('glIndexi', c);
}

export function glIndexiv(c) {
  return call('glIndexiv', c);
}

export function glIndexMask(mask) {
  return call('glIndexMask', mask);
}

export function glIndexPointer(type, stride, pointer) {
  return call('glIndexPointer', type, stride, pointer);
}

export function glIndexs(c) {
  return call('glIndexs', c);
}

export function glIndexsv(c) {
  return call('glIndexsv', c);
}

export function glIndexub(c) {
  return call('glIndexub', c);
}

export function glIndexubv(c) {
  return call('glIndexubv', c);
}

export function glInterleavedArrays(format, stride, pointer) {
  return call('glInterleavedArrays', format, stride, pointer);
}

export function glIsEnabled(cap) {
  return call('glIsEnabled', cap);
}

export function glIsList(list) {
  return call('glIsList', list);
}

export function glIsTexture(texture) {
  return call('glIsTexture', texture);
}

export function glLightf(light, pname, param) {
  return call('glLightf', light, pname, param);
}

export function glLightfv(light, pname, params) {
  return call('glLightfv', light, pname, params);
}

export function glLighti(light, pname, param) {
  return call('glLighti', light, pname, param);
}

export function glLightiv(light, pname, params) {
  return call('glLightiv', light, pname, params);
}

export function glLightModelf(pname, param) {
  return call('glLightModelf', pname, param);
}

export function glLightModelfv(pname, params) {
  return call('glLightModelfv', pname, params);
}

export function glLightModeli(pname, param) {
  return call('glLightModeli', pname, param);
}

export function glLightModeliv(pname, params) {
  return call('glLightModeliv', pname, params);
}

export function glLineStipple(factor, pattern) {
  return call('glLineStipple', factor, pattern);
}

export function glLineWidth(width) {
  return call('glLineWidth', width);
}

export function glListBase(base) {
  return call('glListBase', base);
}

export function glLoadMatrixd(m) {
  return call('glLoadMatrixd', m);
}

export function glLoadMatrixf(m) {
  return call('glLoadMatrixf', m);
}

export function glLoadName(name) {
  return call('glLoadName', name);
}

export function glLogicOp(opcode) {
  return call('glLogicOp', opcode);
}

export function glMap1d(target, u1, u2, stride, order, points) {
  return call('glMap1d', target, u1, u2, stride, order, points);
}

export function glMap1f(target, u1, u2, stride, order, points) {
  return call('glMap1f', target, u1, u2, stride, order, points);
}

export function glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) {
  return call('glMap2d', target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

export function glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) {
  return call('glMap2f', target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

export function glMapGrid1d(un, u1, u2) {
  return call('glMapGrid1d', un, u1, u2);
}

export function glMapGrid1f(un, u1, u2) {
  return call('glMapGrid1f', un, u1, u2);
}

export function glMapGrid2d(un, u1, u2, vn, v1, v2) {
  return call('glMapGrid2d', un, u1, u2, vn, v1, v2);
}

export function glMapGrid2f(un, u1, u2, vn, v1, v2) {
  return call('glMapGrid2f', un, u1, u2, vn, v1, v2);
}

export function glMaterialf(face, pname, param) {
  return call('glMaterialf', face, pname, param);
}

export function glMaterialfv(face, pname, params) {
  return call('glMaterialfv', face, pname, params);
}

export function glMateriali(face, pname, param) {
  return call('glMateriali', face, pname, param);
}

export function glMaterialiv(face, pname, params) {
  return call('glMaterialiv', face, pname, params);
}

export function glMatrixMode(mode) {
  return call('glMatrixMode', mode);
}

export function glMultMatrixd(m) {
  return call('glMultMatrixd', m);
}

export function glMultMatrixf(m) {
  return call('glMultMatrixf', m);
}

export function glNewList(list, mode) {
  return call('glNewList', list, mode);
}

export function glNormal3b(nx, ny, nz) {
  return call('glNormal3b', nx, ny, nz);
}

export function glNormal3bv(v) {
  return call('glNormal3bv', v);
}

export function glNormal3d(nx, ny, nz) {
  return call('glNormal3d', nx, ny, nz);
}

export function glNormal3dv(v) {
  return call('glNormal3dv', v);
}

export function glNormal3f(nx, ny, nz) {
  return call('glNormal3f', nx, ny, nz);
}

export function glNormal3fv(v) {
  return call('glNormal3fv', v);
}

export function glNormal3i(nx, ny, nz) {
  return call('glNormal3i', nx, ny, nz);
}

export function glNormal3iv(v) {
  return call('glNormal3iv', v);
}

export function glNormal3s(nx, ny, nz) {
  return call('glNormal3s', nx, ny, nz);
}

export function glNormal3sv(v) {
  return call('glNormal3sv', v);
}

export function glNormalPointer(type, stride, pointer) {
  return call('glNormalPointer', type, stride, pointer);
}

export function glOrtho(left, right, bottom, top, zNear, zFar) {
  return call('glOrtho', left, right, bottom, top, zNear, zFar);
}

export function glPassThrough(token) {
  return call('glPassThrough', token);
}

export function glPixelMapfv(map, mapsize, values) {
  return call('glPixelMapfv', map, mapsize, values);
}

export function glPixelMapuiv(map, mapsize, values) {
  return call('glPixelMapuiv', map, mapsize, values);
}

export function glPixelMapusv(map, mapsize, values) {
  return call('glPixelMapusv', map, mapsize, values);
}

export function glPixelStoref(pname, param) {
  return call('glPixelStoref', pname, param);
}

export function glPixelStorei(pname, param) {
  return call('glPixelStorei', pname, param);
}

export function glPixelTransferf(pname, param) {
  return call('glPixelTransferf', pname, param);
}

export function glPixelTransferi(pname, param) {
  return call('glPixelTransferi', pname, param);
}

export function glPixelZoom(xfactor, yfactor) {
  return call('glPixelZoom', xfactor, yfactor);
}

export function glPointSize(size) {
  return call('glPointSize', size);
}

export function glPolygonMode(face, mode) {
  return call('glPolygonMode', face, mode);
}

export function glPolygonOffset(factor, units) {
  return call('glPolygonOffset', factor, units);
}

export function glPolygonStipple(mask) {
  return call('glPolygonStipple', mask);
}

export function glPrioritizeTextures(n, textures, priorities) {
  return call('glPrioritizeTextures', n, textures, priorities);
}

export function glPushAttrib(mask) {
  return call('glPushAttrib', mask);
}

export function glPushClientAttrib(mask) {
  return call('glPushClientAttrib', mask);
}

export function glPushName(name) {
  return call('glPushName', name);
}

export function glRasterPos2d(x, y) {
  return call('glRasterPos2d', x, y);
}

export function glRasterPos2dv(v) {
  return call('glRasterPos2dv', v);
}

export function glRasterPos2f(x, y) {
  return call('glRasterPos2f', x, y);
}

export function glRasterPos2fv(v) {
  return call('glRasterPos2fv', v);
}

export function glRasterPos2i(x, y) {
  return call('glRasterPos2i', x, y);
}

export function glRasterPos2iv(v) {
  return call('glRasterPos2iv', v);
}

export function glRasterPos2s(x, y) {
  return call('glRasterPos2s', x, y);
}

export function glRasterPos2sv(v) {
  return call('glRasterPos2sv', v);
}

export function glRasterPos3d(x, y, z) {
  return call('glRasterPos3d', x, y, z);
}

export function glRasterPos3dv(v) {
  return call('glRasterPos3dv', v);
}

export function glRasterPos3f(x, y, z) {
  return call('glRasterPos3f', x, y, z);
}

export function glRasterPos3fv(v) {
  return call('glRasterPos3fv', v);
}

export function glRasterPos3i(x, y, z) {
  return call('glRasterPos3i', x, y, z);
}

export function glRasterPos3iv(v) {
  return call('glRasterPos3iv', v);
}

export function glRasterPos3s(x, y, z) {
  return call('glRasterPos3s', x, y, z);
}

export function glRasterPos3sv(v) {
  return call('glRasterPos3sv', v);
}

export function glRasterPos4d(x, y, z, w) {
  return call('glRasterPos4d', x, y, z, w);
}

export function glRasterPos4dv(v) {
  return call('glRasterPos4dv', v);
}

export function glRasterPos4f(x, y, z, w) {
  return call('glRasterPos4f', x, y, z, w);
}

export function glRasterPos4fv(v) {
  return call('glRasterPos4fv', v);
}

export function glRasterPos4i(x, y, z, w) {
  return call('glRasterPos4i', x, y, z, w);
}

export function glRasterPos4iv(v) {
  return call('glRasterPos4iv', v);
}

export function glRasterPos4s(x, y, z, w) {
  return call('glRasterPos4s', x, y, z, w);
}

export function glRasterPos4sv(v) {
  return call('glRasterPos4sv', v);
}

export function glReadBuffer(mode) {
  return call('glReadBuffer', mode);
}

export function glReadPixels(x, y, width, height, format, type, pixels) {
  return call('glReadPixels', x, y, width, height, format, type, pixels);
}

export function glRectd(x1, y1, x2, y2) {
  return call('glRectd', x1, y1, x2, y2);
}

export function glRectdv(v1, v2) {
  return call('glRectdv', v1, v2);
}

export function glRectf(x1, y1, x2, y2) {
  return call('glRectf', x1, y1, x2, y2);
}

export function glRectfv(v1, v2) {
  return call('glRectfv', v1, v2);
}

export function glRecti(x1, y1, x2, y2) {
  return call('glRecti', x1, y1, x2, y2);
}

export function glRectiv(v1, v2) {
  return call('glRectiv', v1, v2);
}

export function glRects(x1, y1, x2, y2) {
  return call('glRects', x1, y1, x2, y2);
}

export function glRectsv(v1, v2) {
  return call('glRectsv', v1, v2);
}

export function glRenderMode(mode) {
  return call('glRenderMode', mode);
}

export function glRotated(angle, x, y, z) {
  return call('glRotated', angle, x, y, z);
}

export function glRotatef(angle, x, y, z) {
  return call('glRotatef', angle, x, y, z);
}

export function glScaled(x, y, z) {
  return call('glScaled', x, y, z);
}

export function glScalef(x, y, z) {
  return call('glScalef', x, y, z);
}

export function glScissor(x, y, width, height) {
  return call('glScissor', x, y, width, height);
}

export function glSelectBuffer(size, buffer) {
  return call('glSelectBuffer', size, buffer);
}

export function glShadeModel(mode) {
  return call('glShadeModel', mode);
}

export function glStencilFunc(func, ref, mask) {
  return call('glStencilFunc', func, ref, mask);
}

export function glStencilMask(mask) {
  return call('glStencilMask', mask);
}

export function glStencilOp(fail, zfail, zpass) {
  return call('glStencilOp', fail, zfail, zpass);
}

export function glTexCoord1d(s) {
  return call('glTexCoord1d', s);
}

export function glTexCoord1dv(v) {
  return call('glTexCoord1dv', v);
}

export function glTexCoord1f(s) {
  return call('glTexCoord1f', s);
}

export function glTexCoord1fv(v) {
  return call('glTexCoord1fv', v);
}

export function glTexCoord1i(s) {
  return call('glTexCoord1i', s);
}

export function glTexCoord1iv(v) {
  return call('glTexCoord1iv', v);
}

export function glTexCoord1s(s) {
  return call('glTexCoord1s', s);
}

export function glTexCoord1sv(v) {
  return call('glTexCoord1sv', v);
}

export function glTexCoord2d(s, t) {
  return call('glTexCoord2d', s, t);
}

export function glTexCoord2dv(v) {
  return call('glTexCoord2dv', v);
}

export function glTexCoord2f(s, t) {
  return call('glTexCoord2f', s, t);
}

export function glTexCoord2fv(v) {
  return call('glTexCoord2fv', v);
}

export function glTexCoord2i(s, t) {
  return call('glTexCoord2i', s, t);
}

export function glTexCoord2iv(v) {
  return call('glTexCoord2iv', v);
}

export function glTexCoord2s(s, t) {
  return call('glTexCoord2s', s, t);
}

export function glTexCoord2sv(v) {
  return call('glTexCoord2sv', v);
}

export function glTexCoord3d(s, t, r) {
  return call('glTexCoord3d', s, t, r);
}

export function glTexCoord3dv(v) {
  return call('glTexCoord3dv', v);
}

export function glTexCoord3f(s, t, r) {
  return call('glTexCoord3f', s, t, r);
}

export function glTexCoord3fv(v) {
  return call('glTexCoord3fv', v);
}

export function glTexCoord3i(s, t, r) {
  return call('glTexCoord3i', s, t, r);
}

export function glTexCoord3iv(v) {
  return call('glTexCoord3iv', v);
}

export function glTexCoord3s(s, t, r) {
  return call('glTexCoord3s', s, t, r);
}

export function glTexCoord3sv(v) {
  return call('glTexCoord3sv', v);
}

export function glTexCoord4d(s, t, r, q) {
  return call('glTexCoord4d', s, t, r, q);
}

export function glTexCoord4dv(v) {
  return call('glTexCoord4dv', v);
}

export function glTexCoord4f(s, t, r, q) {
  return call('glTexCoord4f', s, t, r, q);
}

export function glTexCoord4fv(v) {
  return call('glTexCoord4fv', v);
}

export function glTexCoord4i(s, t, r, q) {
  return call('glTexCoord4i', s, t, r, q);
}

export function glTexCoord4iv(v) {
  return call('glTexCoord4iv', v);
}

export function glTexCoord4s(s, t, r, q) {
  return call('glTexCoord4s', s, t, r, q);
}

export function glTexCoord4sv(v) {
  return call('glTexCoord4sv', v);
}

export function glTexCoordPointer(size, type, stride, pointer) {
  return call('glTexCoordPointer', size, type, stride, pointer);
}

export function glTexEnvf(target, pname, param) {
  return call('glTexEnvf', target, pname, param);
}

export function glTexEnvfv(target, pname, params) {
  return call('glTexEnvfv', target, pname, params);
}

export function glTexEnvi(target, pname, param) {
  return call('glTexEnvi', target, pname, param);
}

export function glTexEnviv(target, pname, params) {
  return call('glTexEnviv', target, pname, params);
}

export function glTexGend(coord, pname, param) {
  return call('glTexGend', coord, pname, param);
}

export function glTexGendv(coord, pname, params) {
  return call('glTexGendv', coord, pname, params);
}

export function glTexGenf(coord, pname, param) {
  return call('glTexGenf', coord, pname, param);
}

export function glTexGenfv(coord, pname, params) {
  return call('glTexGenfv', coord, pname, params);
}

export function glTexGeni(coord, pname, param) {
  return call('glTexGeni', coord, pname, param);
}

export function glTexGeniv(coord, pname, params) {
  return call('glTexGeniv', coord, pname, params);
}

export function glTexImage1D(target, level, internalformat, width, border, format, type, pixels) {
  return call('glTexImage1D', target, level, internalformat, width, border, format, type, pixels);
}

export function glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) {
  return call('glTexImage2D', target, level, internalformat, width, height, border, format, type, pixels);
}

export function glTexParameterf(target, pname, param) {
  return call('glTexParameterf', target, pname, param);
}

export function glTexParameterfv(target, pname, params) {
  return call('glTexParameterfv', target, pname, params);
}

export function glTexParameteri(target, pname, param) {
  return call('glTexParameteri', target, pname, param);
}

export function glTexParameteriv(target, pname, params) {
  return call('glTexParameteriv', target, pname, params);
}

export function glTexSubImage1D(target, level, xoffset, width, format, type, pixels) {
  return call('glTexSubImage1D', target, level, xoffset, width, format, type, pixels);
}

export function glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) {
  return call('glTexSubImage2D', target, level, xoffset, yoffset, width, height, format, type, pixels);
}

export function glTranslated(x, y, z) {
  return call('glTranslated', x, y, z);
}

export function glTranslatef(x, y, z) {
  return call('glTranslatef', x, y, z);
}

export function glVertex2d(x, y) {
  return call('glVertex2d', x, y);
}

export function glVertex2dv(v) {
  return call('glVertex2dv', v);
}

export function glVertex2f(x, y) {
  return call('glVertex2f', x, y);
}

export function glVertex2fv(v) {
  return call('glVertex2fv', v);
}

export function glVertex2i(x, y) {
  return call('glVertex2i', x, y);
}

export function glVertex2iv(v) {
  return call('glVertex2iv', v);
}

export function glVertex2s(x, y) {
  return call('glVertex2s', x, y);
}

export function glVertex2sv(v) {
  return call('glVertex2sv', v);
}

export function glVertex3d(x, y, z) {
  return call('glVertex3d', x, y, z);
}

export function glVertex3dv(v) {
  return call('glVertex3dv', v);
}

export function glVertex3f(x, y, z) {
  console.log('glVertex3f', { x, y, z });
  return call('glVertex3f', x, y, z);
}

export function glVertex3fv(v) {
  return call('glVertex3fv', v);
}

export function glVertex3i(x, y, z) {
  return call('glVertex3i', x, y, z);
}

export function glVertex3iv(v) {
  return call('glVertex3iv', v);
}

export function glVertex3s(x, y, z) {
  return call('glVertex3s', x, y, z);
}

export function glVertex3sv(v) {
  return call('glVertex3sv', v);
}

export function glVertex4d(x, y, z, w) {
  return call('glVertex4d', x, y, z, w);
}

export function glVertex4dv(v) {
  return call('glVertex4dv', v);
}

export function glVertex4f(x, y, z, w) {
  return call('glVertex4f', x, y, z, w);
}

export function glVertex4fv(v) {
  return call('glVertex4fv', v);
}

export function glVertex4i(x, y, z, w) {
  return call('glVertex4i', x, y, z, w);
}

export function glVertex4iv(v) {
  return call('glVertex4iv', v);
}

export function glVertex4s(x, y, z, w) {
  return call('glVertex4s', x, y, z, w);
}

export function glVertex4sv(v) {
  return call('glVertex4sv', v);
}

export function glVertexPointer(size, type, stride, pointer) {
  return call('glVertexPointer', size, type, stride, pointer);
}

export function glViewport(x, y, width, height) {
  return call('glViewport', x, y, width, height);
}
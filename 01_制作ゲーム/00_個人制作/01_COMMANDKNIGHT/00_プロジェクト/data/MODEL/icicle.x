xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 22;
 0.00000;60.48156;-16.30163;,
 16.13648;60.48156;-4.57779;,
 16.13648;-0.64473;-4.57779;,
 0.00000;-0.64473;-16.30163;,
 9.97291;60.48156;14.39178;,
 9.97291;-0.64473;14.39178;,
 -9.97291;60.48156;14.39178;,
 -9.97291;-0.64473;14.39178;,
 -16.13648;60.48156;-4.57779;,
 -16.13648;-0.64473;-4.57779;,
 0.00000;60.48156;-16.30163;,
 0.00000;-0.64473;-16.30163;,
 0.00000;87.99860;0.66528;,
 0.00000;87.99860;0.66528;,
 0.00000;87.99860;0.66528;,
 0.00000;87.99860;0.66528;,
 0.00000;87.99860;0.66528;,
 0.00000;-0.64473;0.66528;,
 0.00000;-0.64473;0.66528;,
 0.00000;-0.64473;0.66528;,
 0.00000;-0.64473;0.66528;,
 0.00000;-0.64473;0.66528;;
 
 15;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 3;12,1,0;,
 3;13,4,1;,
 3;14,6,4;,
 3;15,8,6;,
 3;16,10,8;,
 3;17,3,2;,
 3;18,2,5;,
 3;19,5,7;,
 3;20,7,9;,
 3;21,9,11;;
 
 MeshMaterialList {
  1;
  15;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.175686;0.800000;0.762353;0.800000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  16;
  0.525976;0.446381;-0.723943;,
  0.572124;0.229300;-0.787462;,
  0.925717;0.229300;0.300783;,
  0.000000;0.229300;0.973356;,
  -0.925717;0.229300;0.300783;,
  0.587785;0.000000;-0.809017;,
  0.951057;0.000000;0.309016;,
  0.000000;0.000000;1.000000;,
  -0.951057;0.000000;0.309016;,
  0.000000;-1.000000;-0.000000;,
  -0.572124;0.229300;-0.787462;,
  -0.587785;0.000000;-0.809017;,
  0.851047;0.446381;0.276521;,
  0.000000;0.446380;0.894843;,
  -0.851047;0.446381;0.276521;,
  -0.525976;0.446381;-0.723943;;
  15;
  4;1,1,5,5;,
  4;2,2,6,6;,
  4;3,3,7,7;,
  4;4,4,8,8;,
  4;10,10,11,11;,
  3;0,1,1;,
  3;12,2,2;,
  3;13,3,3;,
  3;14,4,4;,
  3;15,10,10;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  22;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;;
 }
}

attribute vec3 tangent;
attribute vec3 binormal;

varying vec3 tbnHalfVector;
varying vec3 mvNormal;
varying vec3 mvVertex;

uniform float normalmapOn;

void main(void)
{
    gl_Position = ftransform();
    gl_TexCoord[0] = gl_MultiTexCoord0;
    // gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	mvNormal = normalize(gl_NormalMatrix * gl_Normal);

	mvVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	vec3 mvDirToLight;

	if (normalmapOn == 1.0)
	{
		vec3 mvTangent = gl_NormalMatrix * tangent;
		vec3 mvBinormal = gl_NormalMatrix * binormal;

		vec3 mvDirToEye = -mvVertex;
		vec3 tbnDirToEye;
		tbnDirToEye.x = dot(mvDirToEye, mvTangent);
		tbnDirToEye.y = dot(mvDirToEye, mvBinormal);
		tbnDirToEye.z = dot(mvDirToEye, mvNormal);
	}

	tbnHalfVector = normalize(gl_LightSource[0].halfVector.xyz);
}

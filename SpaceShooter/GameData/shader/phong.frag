uniform sampler2D colormap;
uniform sampler2D normalmap;
uniform sampler2D specularmap;
uniform sampler2D illumination;

uniform float colormapOn;
uniform float normalmapOn;
uniform float specularmapOn;
uniform float illuminationOn;

varying vec3 tbnHalfVector;
varying vec3 mvNormal;
varying vec3 mvVertex;

void main(void)
{
    vec3 tbnNormDirToLight;

	if (gl_LightSource[0].position.w == 0.0)
		tbnNormDirToLight = normalize(gl_LightSource[0].position.xyz);
	else
		tbnNormDirToLight = normalize(gl_LightSource[0].position.xyz - mvVertex);

    vec3 normal = mvNormal;

	if (normalmapOn == 1.0)
		normal = normalize(texture2D(normalmap, gl_TexCoord[0].xy).xyz * 2.0 - 1.0);
		// normal.y = -normal.y;

	float diffuseIntensity = max(dot(tbnNormDirToLight, normal), 0.0);

	vec4 ambient = gl_FrontMaterial.ambient * (gl_LightSource[0].ambient + gl_LightModel.ambient);
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseIntensity;
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	// Colormap
	float baseA = 1.0;
	if (colormapOn == 1.0)
	{
	    vec4 baseColor = texture2D(colormap, gl_TexCoord[0].xy);
		baseA = baseColor.a;
		diffuse *= baseColor;
		ambient *= baseColor;
	}

    // Specular
    if (diffuseIntensity > 0.0)
	{
        float specularModifier = max(dot(normal, tbnHalfVector), 0.0); 
        specular = gl_LightSource[0].specular * gl_FrontMaterial.specular * pow(specularModifier, gl_FrontMaterial.shininess);

		if (specularmapOn == 1.0)
			specular *= texture2D(specularmap, gl_TexCoord[0].xy);
    }

    gl_FragColor = clamp(ambient + diffuse + specular, 0.0, 1.0);

	if (illuminationOn == 1.0)
		gl_FragColor += texture2D(illumination, gl_TexCoord[0].xy);
    gl_FragColor.a = baseA;
}

#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 luzDir;
uniform float innerCutOff;
uniform float outerCutOff;
uniform int iluminacionNocturna;

uniform int nTexturas;
uniform sampler2D objectTexture;
uniform sampler2D objectTexture2;

void main() {
    if (iluminacionNocturna == 1) {
        float ambientI = 0.5;
        vec3 ambient = ambientI * lightColor;
        vec3 ld = luzDir;
        vec3 fd = normalize(vec3(FragPos - lightPos));

        if (acos(dot(fd, ld)) < radians(15.0)) {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;

            float specularStrength = 1.0;
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
            vec3 specular = specularStrength * spec * lightColor;
            vec3 result = (ambient + diffuse + specular) * objectColor;

            vec4 textColor;
            if (nTexturas == 1) {
                textColor = mix(texture(objectTexture, TextCoord), texture(objectTexture2, TextCoord), 0.3);
            } else {
                textColor = texture(objectTexture, TextCoord);
            }

            if (textColor.a < 0.1) {
                discard;
            } else {
                FragColor = mix(vec4(result, 1.0), textColor, 0.5);
            }
        } else {
            vec3 result = ambient * objectColor;
            vec4 textColor;

            if (nTexturas == 1) {
                textColor = mix(texture(objectTexture, TextCoord), texture(objectTexture2, TextCoord), 0.3);
            } else {
                textColor = texture(objectTexture, TextCoord);
            }

            if (textColor.a < 0.1) {
                discard;
            } else {
                FragColor = mix(vec4(result, 1.0), textColor, 0.2);
            }
        }
    } else {
        vec3 result = lightColor * objectColor;
        vec4 textColor;

        if (nTexturas == 1) {
            textColor = mix(texture(objectTexture, TextCoord), texture(objectTexture2, TextCoord), 0.2);
        } else {
            textColor = texture(objectTexture, TextCoord);
        }

        if (textColor.a < 0.1) {
            discard;
        } else {
            FragColor = mix(vec4(result, 1.0), textColor, 0.9);
        }
    }
}

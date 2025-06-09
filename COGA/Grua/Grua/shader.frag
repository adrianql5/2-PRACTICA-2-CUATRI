#version 330 core  // Versi�n de GLSL

// Variables recibidas desde el vertex shader
in vec3 Normal;         // Normal interpolada del fragmento
in vec3 FragPos;        // Posici�n del fragmento en espacio mundial
in vec2 TextCoord;      // Coordenadas de textura

out vec4 FragColor;     // Color final del fragmento que se enviar� al framebuffer

// Uniforms: variables constantes definidas desde el programa en C++
uniform vec3 objectColor;        // Color base del objeto
uniform vec3 viewPos;            // Posici�n de la c�mara (para iluminaci�n especular)
uniform vec3 lightPos;           // Posici�n de la fuente de luz
uniform vec3 lightColor;         // Color de la luz
uniform vec3 luzDir;             // Direcci�n del spotlight (foco)
uniform float innerCutOff;       // �ngulo interno del cono de luz (para corte duro)
uniform float outerCutOff;       // �ngulo externo del cono (para transici�n suave)
uniform int iluminacionNocturna; // Flag para saber si es noche (1) o d�a (0)

uniform int nTexturas;           //Fla para saber si usa 1 (0) o usa (2)
uniform sampler2D objectTexture; // Textura del objeto
uniform sampler2D objectTexture2;// Segunda textura del objeto

void main(){
    if(iluminacionNocturna == 1) {  // Si es de noche
        // Componente ambiental base (constante, sin importar direcci�n de la luz)
        float ambientI = 0.5;
        vec3 ambient = ambientI * lightColor;

        // Vector direcci�n del foco
        vec3 ld = luzDir;

        // Vector desde la luz hacia el fragmento
        vec3 fd = normalize(vec3(FragPos - lightPos));

        // Si el �ngulo entre direcci�n del foco y direcci�n al fragmento est� dentro del haz principal
        if(acos(dot(fd, ld)) < radians(15.0)) {
            // Normal del fragmento, normalizada
            vec3 norm = normalize(Normal);

            // Vector desde el fragmento hacia la luz
            vec3 lightDir = normalize(lightPos - FragPos);

            // C�lculo de componente difusa (�ngulo entre luz y normal)
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;

            // Componente especular (simula el brillo)
            float specularStrength = 1.0;
            vec3 viewDir = normalize(viewPos - FragPos);         // Direcci�n hacia la c�mara
            vec3 reflectDir = reflect(-lightDir, norm);          // Direcci�n del reflejo
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128); // Nivel de brillo
            vec3 specular = specularStrength * spec * lightColor;

            // Suma de todas las componentes (ambiente + difusa + especular) y multiplicado por color base
            vec3 result = (ambient + diffuse + specular) * objectColor;

            vec4 textColor;
            // Se toma el color de la textura
            //Si uso 2 texturas las mezclo
            if(nTexturas == 1) textColor = mix(texture(objectTexture, TextCoord),texture(objectTexture2, TextCoord), 0.3);
            else textColor = texture(objectTexture, TextCoord);

            // Si el fragmento es casi transparente, se descarta
            if(textColor.a < 0.1)
                discard;
            else
                // Se mezcla color de iluminaci�n y textura (50/50)
                FragColor = mix(vec4(result, 1.0), textColor, 0.5);
        } else {
            // Si est� fuera del haz del spotlight: solo iluminaci�n ambiental
            vec3 result = (ambient) * objectColor;

            vec4 textColor;
            // Se toma el color de la textura
            if(nTexturas==1) textColor = mix(texture(objectTexture, TextCoord),texture(objectTexture2, TextCoord), 0.3);
            else textColor = texture(objectTexture, TextCoord);

            if(textColor.a < 0.1)
                discard;
            else
                // Menor influencia de la textura (mezcla al 20%)
                FragColor = mix(vec4(result, 1.0), textColor, 0.2);
        }
    } else {
        // Si es de d�a, iluminaci�n simple sin spotlight ni especular
        vec3 result = lightColor * objectColor;

        vec4 textColor;
        // Se toma el color de la textura
        if(nTexturas == 1) textColor = mix(texture(objectTexture, TextCoord),texture(objectTexture2, TextCoord), 0.2);
        else textColor = texture(objectTexture, TextCoord);

        if(textColor.a < 0.1)
            discard;
        else
            // Se mezcla con la textura (90% textura, 10% color)
            FragColor = mix(vec4(result, 1.0), textColor, 0.9);
    }
}

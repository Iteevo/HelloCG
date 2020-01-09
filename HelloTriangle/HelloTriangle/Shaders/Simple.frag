/* 
  File.strings
  HelloTriangle

  Created by linhe on 5/6/18.
  Copyright © 2018 Iteevo. All rights reserved.
*/
const char* SimpleFragmentShader = STRINGIFY(
                                             
                                             varying lowp vec4 DestinationColor;
                                             
                                             void main(void)
{
    gl_FragColor = DestinationColor;
}
                                             );

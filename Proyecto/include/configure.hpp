#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

namespace Configure {
static const int predeterminatedSizeWindows =
    60;  // Controla el tamaño de los títulos y lo centrado de los textos de
         // forma Global
// Variables para la Gestión de Memoría Estática a fin de no abarcar cantidades
// excesivas de la misma
static const int maximunIngredientSize =
    20;  // Cantidad Máxima de Ingredientes para Una receta
static const int maximunProcedureSize =
    20;  // Cantidad Máxima de Pasos para una Receta
}  // namespace Configure
#endif  // __CONFIGURE_H__
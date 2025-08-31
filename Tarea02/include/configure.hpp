// Constantes de Configuración para poder Ajustar ciertos parámetros del
// programa con un sólo edit
#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

namespace configure {
inline constexpr int inventoryCapacity =
    500;  // Capacidad del arreglo estático del inventario
inline constexpr int barcodeSize =
    13;  // Tope de caracteres en el código de barras
inline constexpr int minimumYear =
    1900;  // Año mínimo para el entryDate de los Productos
}  // namespace configure

#endif  // __CONFIGURE_H__